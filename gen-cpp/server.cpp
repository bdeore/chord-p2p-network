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

using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;
using namespace ::apache::thrift::server;

class FileStoreHandler : virtual public FileStoreIf {
 public:

  FileStoreHandler() = default;

  RFile file;
  RFileMetadata metadata;
  std::vector<NodeID> finger_table;
  NodeID node_id;

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

    std::cout << calculateSHA("128.226.117.49:9090") << std::endl;
    std::cout << calculateSHA("128.226.127.49:9095") << std::endl;

    printf("readFile succeeded\n");
  }

  void setFingertable(const std::vector<NodeID> &node_list) override {
    this->finger_table = node_list;

    for (const auto &node: finger_table) {
      std::cout << node << std::endl;
    }
    printf("setFingertable succeeded\n");
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
//
//  void getNodeSucc(NodeID &_return) {
//    // Your implementation goes here
//    printf("getNodeSucc\n");
//  }

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

int main(int argc, char **argv) {
  int port = 9090;
  ::std::shared_ptr<FileStoreHandler> handler(new FileStoreHandler());
  ::std::shared_ptr<TProcessor> processor(new FileStoreProcessor(handler));
  ::std::shared_ptr<TServerTransport> serverTransport(new TServerSocket(port));
  ::std::shared_ptr<TTransportFactory> transportFactory(new TBufferedTransportFactory());
  ::std::shared_ptr<TProtocolFactory> protocolFactory(new TBinaryProtocolFactory());

  TSimpleServer server(processor, serverTransport, transportFactory, protocolFactory);
  std::cout << "server is rolling on port 9090" << std::endl;
  server.serve();
  return 0;
}

