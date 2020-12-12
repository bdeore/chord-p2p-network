## Chord Distributed Hash Table

This project is an implementation of peer-to-peer file sharing network using chord dht. nodes.txt file lists the peers
which are part of the chord p2p network. keyspace for each node is calculated by taking SHA256 of `[ip]:[port]`.
following methods are supported:

writeFile, readFile, setFingertable, findSucc, findPred, getNodeSucc.

Apache Thrift is used to perform RPC calls.

read more about chord dht: https://medium.com/techlog/chord-building-a-dht-distributed-hash-table-in-golang-67c3ce17417b

### run the server:

``
make start
``

starts single server on port 9090

to run more servers nodes use: source ~/.bashrc && ./server [port]

upon starting the server nodes mentioned in nodes.txt, run the init script with: init nodes.txt

make sure apache thrift is added to your path.

### make client for testing

``
make client
``

### restart server ( to rebuild ):

``
make restart
``

### server should be running on:

``
[ip]:[port]
``

port will be printed out when the server start.



