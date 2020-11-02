/**
 * Autogenerated by Thrift Compiler (0.13.0)
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
#include "chord_types.h"

#include <algorithm>
#include <ostream>

#include <thrift/TToString.h>




RFileMetadata::~RFileMetadata() noexcept {
}


void RFileMetadata::__set_filename(const std::string& val) {
  this->filename = val;
__isset.filename = true;
}

void RFileMetadata::__set_version(const int32_t val) {
  this->version = val;
__isset.version = true;
}
std::ostream& operator<<(std::ostream& out, const RFileMetadata& obj)
{
  obj.printTo(out);
  return out;
}


uint32_t RFileMetadata::read(::apache::thrift::protocol::TProtocol* iprot) {

  ::apache::thrift::protocol::TInputRecursionTracker tracker(*iprot);
  uint32_t xfer = 0;
  std::string fname;
  ::apache::thrift::protocol::TType ftype;
  int16_t fid;

  xfer += iprot->readStructBegin(fname);

  using ::apache::thrift::protocol::TProtocolException;


  while (true)
  {
    xfer += iprot->readFieldBegin(fname, ftype, fid);
    if (ftype == ::apache::thrift::protocol::T_STOP) {
      break;
    }
    switch (fid)
    {
      case 1:
        if (ftype == ::apache::thrift::protocol::T_STRING) {
          xfer += iprot->readString(this->filename);
          this->__isset.filename = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 2:
        if (ftype == ::apache::thrift::protocol::T_I32) {
          xfer += iprot->readI32(this->version);
          this->__isset.version = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      default:
        xfer += iprot->skip(ftype);
        break;
    }
    xfer += iprot->readFieldEnd();
  }

  xfer += iprot->readStructEnd();

  return xfer;
}

uint32_t RFileMetadata::write(::apache::thrift::protocol::TProtocol* oprot) const {
  uint32_t xfer = 0;
  ::apache::thrift::protocol::TOutputRecursionTracker tracker(*oprot);
  xfer += oprot->writeStructBegin("RFileMetadata");

  if (this->__isset.filename) {
    xfer += oprot->writeFieldBegin("filename", ::apache::thrift::protocol::T_STRING, 1);
    xfer += oprot->writeString(this->filename);
    xfer += oprot->writeFieldEnd();
  }
  if (this->__isset.version) {
    xfer += oprot->writeFieldBegin("version", ::apache::thrift::protocol::T_I32, 2);
    xfer += oprot->writeI32(this->version);
    xfer += oprot->writeFieldEnd();
  }
  xfer += oprot->writeFieldStop();
  xfer += oprot->writeStructEnd();
  return xfer;
}

void swap(RFileMetadata &a, RFileMetadata &b) {
  using ::std::swap;
  swap(a.filename, b.filename);
  swap(a.version, b.version);
  swap(a.__isset, b.__isset);
}

RFileMetadata::RFileMetadata(const RFileMetadata& other0) {
  filename = other0.filename;
  version = other0.version;
  __isset = other0.__isset;
}
RFileMetadata& RFileMetadata::operator=(const RFileMetadata& other1) {
  filename = other1.filename;
  version = other1.version;
  __isset = other1.__isset;
  return *this;
}
void RFileMetadata::printTo(std::ostream& out) const {
  using ::apache::thrift::to_string;
  out << "RFileMetadata(";
  out << "filename="; (__isset.filename ? (out << to_string(filename)) : (out << "<null>"));
  out << ", " << "version="; (__isset.version ? (out << to_string(version)) : (out << "<null>"));
  out << ")";
}


RFile::~RFile() noexcept {
}


void RFile::__set_meta(const RFileMetadata& val) {
  this->meta = val;
__isset.meta = true;
}

void RFile::__set_content(const std::string& val) {
  this->content = val;
__isset.content = true;
}
std::ostream& operator<<(std::ostream& out, const RFile& obj)
{
  obj.printTo(out);
  return out;
}


uint32_t RFile::read(::apache::thrift::protocol::TProtocol* iprot) {

  ::apache::thrift::protocol::TInputRecursionTracker tracker(*iprot);
  uint32_t xfer = 0;
  std::string fname;
  ::apache::thrift::protocol::TType ftype;
  int16_t fid;

  xfer += iprot->readStructBegin(fname);

  using ::apache::thrift::protocol::TProtocolException;


  while (true)
  {
    xfer += iprot->readFieldBegin(fname, ftype, fid);
    if (ftype == ::apache::thrift::protocol::T_STOP) {
      break;
    }
    switch (fid)
    {
      case 1:
        if (ftype == ::apache::thrift::protocol::T_STRUCT) {
          xfer += this->meta.read(iprot);
          this->__isset.meta = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 2:
        if (ftype == ::apache::thrift::protocol::T_STRING) {
          xfer += iprot->readString(this->content);
          this->__isset.content = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      default:
        xfer += iprot->skip(ftype);
        break;
    }
    xfer += iprot->readFieldEnd();
  }

  xfer += iprot->readStructEnd();

  return xfer;
}

uint32_t RFile::write(::apache::thrift::protocol::TProtocol* oprot) const {
  uint32_t xfer = 0;
  ::apache::thrift::protocol::TOutputRecursionTracker tracker(*oprot);
  xfer += oprot->writeStructBegin("RFile");

  if (this->__isset.meta) {
    xfer += oprot->writeFieldBegin("meta", ::apache::thrift::protocol::T_STRUCT, 1);
    xfer += this->meta.write(oprot);
    xfer += oprot->writeFieldEnd();
  }
  if (this->__isset.content) {
    xfer += oprot->writeFieldBegin("content", ::apache::thrift::protocol::T_STRING, 2);
    xfer += oprot->writeString(this->content);
    xfer += oprot->writeFieldEnd();
  }
  xfer += oprot->writeFieldStop();
  xfer += oprot->writeStructEnd();
  return xfer;
}

void swap(RFile &a, RFile &b) {
  using ::std::swap;
  swap(a.meta, b.meta);
  swap(a.content, b.content);
  swap(a.__isset, b.__isset);
}

RFile::RFile(const RFile& other2) {
  meta = other2.meta;
  content = other2.content;
  __isset = other2.__isset;
}
RFile& RFile::operator=(const RFile& other3) {
  meta = other3.meta;
  content = other3.content;
  __isset = other3.__isset;
  return *this;
}
void RFile::printTo(std::ostream& out) const {
  using ::apache::thrift::to_string;
  out << "RFile(";
  out << "meta="; (__isset.meta ? (out << to_string(meta)) : (out << "<null>"));
  out << ", " << "content="; (__isset.content ? (out << to_string(content)) : (out << "<null>"));
  out << ")";
}


