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

using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;
using namespace ::apache::thrift::server;

class FileStoreHandler : virtual public FileStoreIf {
 public:
  RFile file;
  RFileMetadata metadata;
  std::vector<NodeID> finger_table;
  NodeID node_id, pred_node_id, temp;

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
    std::cout << "\nNodeID :" << " IP: " << node_id.ip << "  Port: " << node_id.port << "\nHash: " << node_id.id
              << std::endl;
  }

  void writeFile(const RFile &rFile) override {
    std::ifstream exists(rFile.meta.filename.c_str());
    std::ofstream file_stream;

    if (!exists.good()) {
      metadata.version = rFile.meta.version;
      this->metadata.version--;
      std::cout << "this executed " << metadata.version << std::endl;
    }

    file.content = rFile.content;
    this->metadata.filename = rFile.meta.filename;
    this->metadata.version += 1;
    this->file.meta.version = metadata.version;
    file_stream.open(metadata.filename.c_str());
    file_stream << file.content;

    file_stream.close();
    std::cout << file.content << " " << metadata.filename << " " << file.meta.version << " " << metadata.version
              << std::endl;
    printf("writeFile succeeded\n");
  }

  void readFile(RFile &_return, const std::string &filename) override {
    std::ifstream exists(filename.c_str());

    if (exists.good()) {
      RFileMetadata meta;
      meta.__set_filename(this->metadata.filename);
      meta.__set_version(this->metadata.version);
      _return.__set_meta(meta);
      _return.__set_content(this->file.content);

    } else {
      SystemException exception;
      exception.__set_message("Exception: File doesn't exist on the server");
      throw exception;
    }

    printf("readFile succeeded\n");
  }

  void setFingertable(const std::vector<NodeID> &node_list) override {
    this->finger_table = node_list;
    std::cout << this->finger_table.size() << std::endl;
    printf("setFingertable succeeded\n");
  }

//  void findSucc(NodeID &_return, const std::string &key) {
//    // Your implementation goes here
//    printf("findSucc\n");
//  }

  void findPred(NodeID &_return, const std::string &key) override {
    if (finger_table.size() == 0) {
      std::string message = "Exception: Finger Table for the node [ " + node_id.id.substr(0, 8) + " ] is empty";
      SystemException exception;
      exception.__set_message(message);
      throw exception;
    } else {
      temp = finger_table.at(0);

      while (temp.id != node_id.id) {
        auto trans_ep = std::make_shared<TSocket>(temp.ip, temp.port);
        auto trans_buf = std::make_shared<TBufferedTransport>(trans_ep);
        auto proto = std::make_shared<TBinaryProtocol>(trans_buf);
        FileStoreClient temp_client(proto);

        trans_ep->open();
        pred_node_id.__set_ip(temp.ip);
        pred_node_id.__set_id(temp.id);
        pred_node_id.__set_port(temp.port);

        temp_client.getNodeSucc(temp);
        trans_ep->close();
      }

      std::cout << "Predecessor of Node: " << node_id.id.substr(0, 6) << " is Node : " << pred_node_id.id.substr(0, 6)
                << std::endl;

      _return.__set_id(pred_node_id.id);
      _return.__set_ip(pred_node_id.ip);
      _return.__set_port(pred_node_id.port);

    }

    printf("findPred succeeded\n");
  }

  void getNodeSucc(NodeID &_return) override {

    if (finger_table.size() != 0) {

      _return.__set_ip(this->finger_table.at(0).ip);
      _return.__set_id(this->finger_table.at(0).id);
      _return.__set_port(this->finger_table.at(0).port);

      std::cout << "Successor of Node : " << node_id.id.substr(0, 6) << " is Node: " << _return.id.substr(0, 6)
                << " IP: " << _return.ip << "  Port: " << _return.port << std::endl;

      printf("getNodeSucc succeeded\n ");
    } else {
      SystemException exception;
      exception.__set_message("Exception: Finger Table for the node is empty");
      throw exception;
    }

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
    std::shared_ptr<FileStoreHandler> handler(new FileStoreHandler(port_in));
    std::shared_ptr<TProcessor> processor(new FileStoreProcessor(handler));
    std::shared_ptr<TServerTransport> serverTransport(new TServerSocket(port_in));
    std::shared_ptr<TTransportFactory> transportFactory(new TBufferedTransportFactory());
    std::shared_ptr<TProtocolFactory> protocolFactory(new TBinaryProtocolFactory());

    TSimpleServer server(processor, serverTransport, transportFactory, protocolFactory);
    std::cout << "\nserver is running on port: [ " << port_in << " ]" << std::endl;
    server.serve();
  } else {
    SystemException exception;
    std::cerr << "\nInvalid Arguments: [ Usage ] : ./server 9090 [port]\n" << std::endl;
    exception.__set_message("[ Usage ] : ./server 9090 [port]");
    throw exception;
  }
  return 0;
}

