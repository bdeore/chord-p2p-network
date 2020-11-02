#include "FileStore.h"
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/server/TSimpleServer.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TBufferTransports.h>
#include <iostream>
#include <fstream>

using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;
using namespace ::apache::thrift::server;

class FileStoreHandler : virtual public FileStoreIf {
 public:

  FileStoreHandler() = default;

  RFile file;
  RFileMetadata metadata;
  std::ofstream file_stream;

  void writeFile(const RFile &rFile) override {
    std::ifstream exists(rFile.meta.filename.c_str());

    if (!exists.good()) {
      metadata.version = rFile.meta.version;
      this->metadata.version--;
      std::cout << "this executed " << metadata.version << std::endl;
    }

    file.content = rFile.content;
    this->metadata.filename = rFile.meta.filename;
    this->metadata.version += 1;
    this->file.meta.version = metadata.version;
    this->file_stream.open(metadata.filename.c_str());
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
      exception.__set_message("file doesn't exist");
      throw exception;
    }

    printf("readFile succeeded\n");
  }
//
//  void setFingertable(const std::vector<NodeID> &node_list) {
//    // Your implementation goes here
//    printf("setFingertable\n");
//  }
//
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

