#include "FileStore.h"
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/server/TSimpleServer.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TBufferTransports.h>
#include <thrift/transport/TSocket.h>

#include <openssl/sha.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <memory>
#include <map>
#include <utility>

using namespace apache::thrift;
using namespace apache::thrift::protocol;
using namespace apache::thrift::transport;
using namespace apache::thrift::server;

class FileStoreHandler : virtual public FileStoreIf {
 public:
  std::vector<NodeID> finger_table;
  NodeID node_id, pred_node_id;
  std::map<std::string, RFile> available_files;

  FileStoreHandler(int port) {
    std::ifstream input_stream;
    input_stream.open("nodes.txt");
    std::string ip;
    std::getline(input_stream, ip);
    ip = ip.substr(0, 15);
    std::string key = ip + ":" + std::to_string(port);

    std::string id = calculateSHA(key);
    this->node_id.__set_id(id);
    this->node_id.__set_ip(ip);
    this->node_id.__set_port(port);
    input_stream.close();

    std::cout << "     IP: " << node_id.ip << "  |  NodeID: " << node_id.id.substr(0, 8)
              << "\n ------------------------------------------------\n" << std::endl;
  }

  void writeFile(const RFile &rFile) override {
    if (finger_table.size() == 0) {
      std::string message = "Exception: Finger Table for the node [ " + node_id.id.substr(0, 8) + " ] is empty";
      SystemException exception;
      exception.__set_message(message);
      throw exception;
    }

    RFileMetadata metadata;
    std::string file_sha = calculateSHA(rFile.meta.filename);
    NodeID owner;

    findPred(owner, file_sha);
    forward_request(owner, owner);

    if (node_id.id == owner.id) {
      std::ifstream exists(rFile.meta.filename.c_str());
      std::ofstream file_stream;

      if (!exists.good()) {
        RFile file;
        metadata.version = 0;
        file.content = rFile.content;
        metadata.__set_filename(rFile.meta.filename);
        metadata.__set_version(metadata.version);
        file.__set_content(rFile.content);
        file.__set_meta(metadata);
        available_files.insert(std::make_pair(std::string(rFile.meta.filename), file));

        file_stream.open(rFile.meta.filename);
        file_stream << file.content;
        file_stream.close();

      } else {
        std::map<std::string, RFile>::iterator it = available_files.find(rFile.meta.filename);
        it->second.meta.version += 1;
        it->second.content = rFile.content;

        file_stream.open(rFile.meta.filename);
        file_stream << it->second.content;
        file_stream.close();
      }

    } else {
      SystemException exception;
      exception.__set_message("Exception: Server is not the file's successor");
      throw exception;
    }
//    std::cout << file.content << " " << metadata.filename << " " << file.meta.version << " " << metadata.version
//              << std::endl;
//    printf("writeFile succeeded\n");
  }

  void readFile(RFile &_return, const std::string &filename) override {
    if (finger_table.size() == 0) {
      std::string message = "Exception: Finger Table for the node [ " + node_id.id.substr(0, 8) + " ] is empty";
      SystemException exception;
      exception.__set_message(message);
      throw exception;
    }

    std::ifstream exists(filename.c_str());
    if (exists.good()) {
      std::map<std::string, RFile>::iterator it = available_files.find(filename);

      RFile file = it->second;

      _return.__set_meta(it->second.meta);
      _return.__set_content(file.content);

    } else {
      SystemException exception;
      exception.__set_message("Exception: File doesn't exist on the server");
      throw exception;
    }
  }

  void setFingertable(const std::vector<NodeID> &node_list) override {
    this->finger_table = node_list;
  }

  void findSucc(NodeID &_return, const std::string &key) override {
    findPred(pred_node_id, key);
    forward_request(_return, pred_node_id);
  }

  void findPred(NodeID &_return, const std::string &key) override {
    if (finger_table.size() == 0) {
      std::string message = "Exception: Finger Table for the node [ " + node_id.id.substr(0, 8) + " ] is empty";
      SystemException exception;
      exception.__set_message(message);
      throw exception;
    } else {
      NodeID temp;
      temp = finger_table.at(0);
      if (key > node_id.id && key <= finger_table.at(0).id) {
        pred_node_id.__set_ip(temp.ip);
        pred_node_id.__set_id(temp.id);
        pred_node_id.__set_port(temp.port);
      } else {
        while (key > temp.id || key <= pred_node_id.id) {
          pred_node_id.__set_ip(temp.ip);
          pred_node_id.__set_id(temp.id);
          pred_node_id.__set_port(temp.port);
          forward_request(temp, temp);
        }
      }

      _return.__set_id(pred_node_id.id);
      _return.__set_ip(pred_node_id.ip);
      _return.__set_port(pred_node_id.port);
    }
//      std::cout << "Predecessor of Node: " << key.substr(0, 6) << " is Node : " << pred_node_id.id.substr(0, 6)
//                << std::endl;
//    printf("findPred succeeded\n");
  }

  void getNodeSucc(NodeID &_return) override {

    if (finger_table.size() != 0) {
      _return.__set_ip(this->finger_table.at(0).ip);
      _return.__set_id(this->finger_table.at(0).id);
      _return.__set_port(this->finger_table.at(0).port);

    } else {
      SystemException exception;
      exception.__set_message("Exception: Finger Table for the node is empty");
      throw exception;
    }
//      std::cout << "Successor of Node : " << node_id.id.substr(0, 6) << " is Node: " << _return.id.substr(0, 6)
//                << " IP: " << _return.ip << "  Port: " << _return.port << std::endl;
  }

  void forward_request(NodeID &_return, NodeID node) {
    auto trans_ep = std::make_shared<TSocket>(node.ip, node.port);
    auto trans_buf = std::make_shared<TBufferedTransport>(trans_ep);
    auto proto = std::make_shared<TBinaryProtocol>(trans_buf);
    FileStoreClient temp_client(proto);

    trans_ep->open();
    temp_client.getNodeSucc(_return);
    trans_ep->close();
  }

  std::string calculateSHA(std::string key) {
    unsigned char hash[SHA256_DIGEST_LENGTH];

    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, key.c_str(), key.size());
    SHA256_Final(hash, &sha256);

    std::ostringstream sha_str;
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
      sha_str << std::hex << std::setw(2) << std::setfill('0') << (int) hash[i];
    }
    return sha_str.str();
  }
};

int main(int argc, char *argv[]) {
  if (argc > 1) {
    int port_in = std::stoi(argv[1]);

    std::cout << "\n ------------------------------------------------\n"
              << "       server is running on port: [ " << port_in << " ]\n"
              << " ------------------------------------------------\n";

    std::shared_ptr<FileStoreHandler> handler(new FileStoreHandler(port_in));
    std::shared_ptr<TProcessor> processor(new FileStoreProcessor(handler));
    std::shared_ptr<TServerTransport> serverTransport(new TServerSocket(port_in));
    std::shared_ptr<TTransportFactory> transportFactory(new TBufferedTransportFactory());
    std::shared_ptr<TProtocolFactory> protocolFactory(new TBinaryProtocolFactory());

    TSimpleServer server(processor, serverTransport, transportFactory, protocolFactory);

    server.serve();
  } else {
    SystemException exception;
    std::cerr << "\nInvalid Arguments: [ Usage ] : ./server 9090 [port]\n" << std::endl;
    exception.__set_message("[ Usage ] : ./server 9090 [port]");
    throw exception;
  }
  return 0;
}

