SHELL	:= /bin/bash
GEN_SRC := server.cpp	FileStore.cpp	chord_types.cpp	chord_constants.cpp
GEN_OBJ := $(patsubst	%.cpp,%.o,	$(GEN_SRC))

THRIFT_DIR := /home/cs557-inst/local/include
LIB_DIR := /home/cs557-inst/local/lib

INC := -I$(THRIFT_DIR) -Isrc/ -I$(THRIFT_DIR)/thrift

.PHONY: all clean

all:server	client

%.o:gen-cpp/%.cpp
	$(CXX)	-std=c++17	-lstdc++	-Wall	-DHAVE_INTTYPES_H	-DHAVE_NETINET_IN_H	$(INC)	-c	$<	-o	$@

server:server.o	$(GEN_OBJ)
	$(CXX)	$^	-o	$@	-std=c++17	-lstdc++	-L$(LIB_DIR)	-lthrift	 -lssl	-lcrypto

client:
	g++	-std=c++17	-lstdc++	-Wall	-DHAVE_INTTYPES_H	-DHAVE_NETINET_IN_H	-I/home/cs557-inst/local/include -Isrc/ -I/home/cs557-inst/local/include/thrift	-c	gen-cpp/client.cpp	-o	client.o
	g++	client.o	FileStore.o	chord_types.o	chord_constants.o	-o	client	-std=c++17	-lstdc++	-L/home/cs557-inst/local/lib/	-lthrift	 -lssl	-lcrypto

run:
	source	~/.bashrc && ./server 9090

re:clean all run

clean:
	$(RM)	*.o	server