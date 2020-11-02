#include "FileStore.h"
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/server/TSimpleServer.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TBufferTransports.h>

#include <openssl/sha.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>

using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;
using namespace ::apache::thrift::server;

class FileStoreHandler : virtual public FileStoreIf {
 public:
  RFile file;
  RFileMetadata metadata;
  std::vector<NodeID> finger_table;
  NodeID node_id;
  int port;

  FileStoreHandler() {
    std::string ip = "128.226.114.201";

    std::string key = ip + ":" + std::to_string(port);
    this->node_id.__set_id(calculateSHA(key));
    this->node_id.__set_ip(ip);
    this->node_id.__set_port(port);
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
//    for (const auto &node: finger_table) {
//      std::cout << node << std::endl;
//    }
  }

//  void findSucc(NodeID &_return, const std::string &key) {
//    // Your implementation goes here
//    printf("findSucc\n");
//  }
//
//  void findPred(NodeID &_return, const std::string &key) {
//    // Your implementation goes here
//    printf("findPred\n");
//  }

  void getNodeSucc(NodeID &_return) override {

    if (finger_table.size() != 0) {
      _return = this->finger_table.at(0);

    } else {
      SystemException exception;
      exception.__set_message("Exception: Finger Table for the node is empty");
      throw exception;
    }

    printf("getNodeSucc succeeded\n");
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
  int port = std::stoi(argv[1]);
  ::std::shared_ptr<FileStoreHandler> handler(new FileStoreHandler());
  ::std::shared_ptr<TProcessor> processor(new FileStoreProcessor(handler));
  ::std::shared_ptr<TServerTransport> serverTransport(new TServerSocket(port));
  ::std::shared_ptr<TTransportFactory> transportFactory(new TBufferedTransportFactory());
  ::std::shared_ptr<TProtocolFactory> protocolFactory(new TBinaryProtocolFactory());
  handler->port = port;

  TSimpleServer server(processor, serverTransport, transportFactory, protocolFactory);
  std::cout << "server is running on port: [ " << handler->port << " ]" << std::endl;
  server.serve();
  return 0;
}

