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

int main(int argc, char *argv[]) {
  auto trans_ep = make_shared<TSocket>("128.226.114.205", 9092);
  auto trans_buf = make_shared<TBufferedTransport>(trans_ep);
  auto proto = make_shared<TBinaryProtocol>(trans_buf);
  FileStoreClient client(proto);

  trans_ep->open();

  RFile file;
  RFileMetadata metadata;

  metadata.__set_filename("sample.txt");
  file.__set_content("this is original content");
  file.__set_meta(metadata);

  client.writeFile(file);

  RFile newFile;
  RFileMetadata newMetadata;
  newFile.__set_meta(newMetadata);

  client.readFile(newFile, "sample.txt");
  std::cout << "File Content: " << newFile.content << "\n" << "File Name: " << newFile.meta.filename << "\n"
            << "File Version: " << newFile.meta.version << "\n" << std::endl;

  metadata.__set_filename("sample.txt");
  file.__set_content("this is updated content");
  file.__set_meta(metadata);

  client.writeFile(file);

  client.readFile(newFile, "sample.txt");
  std::cout << "File Content: " << newFile.content << "\n" << "File Name: " << newFile.meta.filename << "\n"
            << "File Version: " << newFile.meta.version << "\n" << std::endl;

  NodeID node_id, succ;

  client.findPred(node_id, std::string("3b87c83054b11546279bab823d25e8ca4fc7cb569d74f1c19d905a30e093acfd"));

  std::cout << "\nPredecessor NodeID for Key []: " << " IP: " << node_id.ip << "  Port: " << node_id.port
            << "\nHash: " << node_id.id << std::endl;

  client.findSucc(succ, std::string("3b87c83054b11546279bab823d25e8ca4fc7cb569d74f1c19d905a30e093acfd"));

  std::cout << "\nSuccessor NodeID for Key []: " << " IP: " << succ.ip << "  Port: " << succ.port
            << "\nHash: " << succ.id << std::endl << std::endl;

  trans_ep->close();
}

