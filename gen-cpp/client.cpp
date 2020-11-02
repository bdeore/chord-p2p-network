#include "FileStore.h"
#include "chord_types.h"
#include "chord_constants.h"
#include <thrift/transport/TSocket.h>
#include <thrift/transport/TBufferTransports.h>
#include <thrift/protocol/TBinaryProtocol.h>
#include <iostream>
#include <memory>
#include <string>

using namespace apache::thrift::transport;
using namespace apache::thrift::protocol;

using std::make_shared;

//struct RFileMetadata {
//  std::string filename;
//  int version;
//} metadata;
//
//struct RFile {
//  RFileMetadata meta;
//  std::string content;
//} file;

int main() {
  auto trans_ep = make_shared<TSocket>("localhost", 9090);
  auto trans_buf = make_shared<TBufferedTransport>(trans_ep);
  auto proto = make_shared<TBinaryProtocol>(trans_buf);
  FileStoreClient client(proto);

  trans_ep->open();

  RFileMetadata metadata;
  RFile file;

  metadata.__set_filename("sample.txt");

  file.__set_content("testing file operation");
  file.__set_meta(metadata);

  client.writeFile(file);

  RFile newFile;
  RFileMetadata newMetadata;
  newFile.__set_meta(newMetadata);

  client.readFile(newFile, "sample.txt");

  std::cout << newFile.content << " " << newFile.meta.filename << " " << newFile.meta.version << " " << std::endl;

  trans_ep->close();
}

