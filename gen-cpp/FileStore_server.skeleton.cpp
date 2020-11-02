// This autogenerated skeleton file illustrates how to build a server.
// You should copy it to another filename to avoid overwriting it.

#include "FileStore.h"
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/server/TSimpleServer.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TBufferTransports.h>

using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;
using namespace ::apache::thrift::server;

class FileStoreHandler : virtual public FileStoreIf {
 public:
  FileStoreHandler() {
    // Your initialization goes here
  }

  void writeFile(const RFile& rFile) {
    // Your implementation goes here
    printf("writeFile\n");
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
  server.serve();
  return 0;
}

