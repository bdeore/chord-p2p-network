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

  RFileMetadata metadata;
  RFile file;

  metadata.__set_filename("sample.txt");

  file.__set_content("testing file operation");
  file.__set_meta(metadata);

  client.writeFile(file);

  std::cout << "writefile successful" << std::endl;
  RFile newFile;
  RFileMetadata newMetadata;
  newFile.__set_meta(newMetadata);

  client.readFile(newFile, "sample.txt");
  std::cout << newFile.content << " " << newFile.meta.filename << " " << newFile.meta.version << " " << std::endl;

  std::cout << "readfile successful" << std::endl;

  metadata.__set_filename("test.txt");

  file.__set_content("test.txt file operation");

  file.__set_meta(metadata);

  client.writeFile(file);

  client.readFile(newFile, "test.txt");

  std::cout << newFile.content << " " << newFile.meta.filename << " " << newFile.meta.version << " " << std::endl;

  NodeID node_id;

  client.findPred(node_id, std::string("8d585cbca8cfad4ffc7ae82baf74800efe4d8fec5831ac0fbb1d03e0ddc535d7"));
  std::cout << "\nPredecessor NodeID for Key [8d585c]: " << " IP: " << node_id.ip << "  Port: " << node_id.port
            << "\nHash: " << node_id.id << std::endl;

  client.findSucc(node_id, std::string("9d585cbca8cfad4ffc7ae82baf74800efe4d8fec5831ac0fbb1d03e0ddc535d7"));

  std::cout << "\nSuccessor NodeID for Key [9d585cb]: " << " IP: " << node_id.ip << "  Port: " << node_id.port
            << "\nHash: " << node_id.id << std::endl;

  trans_ep->close();
}

