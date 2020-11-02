SHELL	:= /bin/bash
GEN_SRC := server.cpp	FileStore.cpp	chord_types.cpp	chord_constants.cpp
GEN_OBJ := $(patsubst	%.cpp,%.o,	$(GEN_SRC))

THRIFT_DIR := /home/cs557-inst/local/include
LIB_DIR := /home/cs557-inst/local/lib/

INC := -I$(THRIFT_DIR) -Isrc/ -I$(THRIFT_DIR)/thrift

.PHONY: all clean

all:server

%.o:gen-cpp/%.cpp
	$(CXX)	-std=c++17	-lstdc++	-Wall	-DHAVE_INTTYPES_H	-DHAVE_NETINET_IN_H	$(INC)	-c	$<	-o	$@

server:server.o	$(GEN_OBJ)
	$(CXX)	$^	-o	$@	-std=c++17	-lstdc++	-L$(LIB_DIR)	-lthrift

run:
	source	~/.bashrc && ./server

clean:
	$(RM)	*.o	server