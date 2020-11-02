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




SystemException::~SystemException() noexcept {
}


void SystemException::__set_message(const std::string& val) {
  this->message = val;
__isset.message = true;
}
std::ostream& operator<<(std::ostream& out, const SystemException& obj)
{
  obj.printTo(out);
  return out;
}


uint32_t SystemException::read(::apache::thrift::protocol::TProtocol* iprot) {

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
          xfer += iprot->readString(this->message);
          this->__isset.message = true;
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

uint32_t SystemException::write(::apache::thrift::protocol::TProtocol* oprot) const {
  uint32_t xfer = 0;
  ::apache::thrift::protocol::TOutputRecursionTracker tracker(*oprot);
  xfer += oprot->writeStructBegin("SystemException");

  if (this->__isset.message) {
    xfer += oprot->writeFieldBegin("message", ::apache::thrift::protocol::T_STRING, 1);
    xfer += oprot->writeString(this->message);
    xfer += oprot->writeFieldEnd();
  }
  xfer += oprot->writeFieldStop();
  xfer += oprot->writeStructEnd();
  return xfer;
}

void swap(SystemException &a, SystemException &b) {
  using ::std::swap;
  swap(a.message, b.message);
  swap(a.__isset, b.__isset);
}

SystemException::SystemException(const SystemException& other0) : TException() {
  message = other0.message;
  __isset = other0.__isset;
}
SystemException& SystemException::operator=(const SystemException& other1) {
  message = other1.message;
  __isset = other1.__isset;
  return *this;
}
void SystemException::printTo(std::ostream& out) const {
  using ::apache::thrift::to_string;
  out << "SystemException(";
  out << "message="; (__isset.message ? (out << to_string(message)) : (out << "<null>"));
  out << ")";
}

const char* SystemException::what() const noexcept {
  try {
    std::stringstream ss;
    ss << "TException - service has thrown: " << *this;
    this->thriftTExceptionMessageHolder_ = ss.str();
    return this->thriftTExceptionMessageHolder_.c_str();
  } catch (const std::exception&) {
    return "TException - service has thrown: SystemException";
  }
}


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

RFileMetadata::RFileMetadata(const RFileMetadata& other2) {
  filename = other2.filename;
  version = other2.version;
  __isset = other2.__isset;
}
RFileMetadata& RFileMetadata::operator=(const RFileMetadata& other3) {
  filename = other3.filename;
  version = other3.version;
  __isset = other3.__isset;
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

RFile::RFile(const RFile& other4) {
  meta = other4.meta;
  content = other4.content;
  __isset = other4.__isset;
}
RFile& RFile::operator=(const RFile& other5) {
  meta = other5.meta;
  content = other5.content;
  __isset = other5.__isset;
  return *this;
}
void RFile::printTo(std::ostream& out) const {
  using ::apache::thrift::to_string;
  out << "RFile(";
  out << "meta="; (__isset.meta ? (out << to_string(meta)) : (out << "<null>"));
  out << ", " << "content="; (__isset.content ? (out << to_string(content)) : (out << "<null>"));
  out << ")";
}


NodeID::~NodeID() noexcept {
}


void NodeID::__set_id(const std::string& val) {
  this->id = val;
}

void NodeID::__set_ip(const std::string& val) {
  this->ip = val;
}

void NodeID::__set_port(const int32_t val) {
  this->port = val;
}
std::ostream& operator<<(std::ostream& out, const NodeID& obj)
{
  obj.printTo(out);
  return out;
}


uint32_t NodeID::read(::apache::thrift::protocol::TProtocol* iprot) {

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
          xfer += iprot->readString(this->id);
          this->__isset.id = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 2:
        if (ftype == ::apache::thrift::protocol::T_STRING) {
          xfer += iprot->readString(this->ip);
          this->__isset.ip = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 3:
        if (ftype == ::apache::thrift::protocol::T_I32) {
          xfer += iprot->readI32(this->port);
          this->__isset.port = true;
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

uint32_t NodeID::write(::apache::thrift::protocol::TProtocol* oprot) const {
  uint32_t xfer = 0;
  ::apache::thrift::protocol::TOutputRecursionTracker tracker(*oprot);
  xfer += oprot->writeStructBegin("NodeID");

  xfer += oprot->writeFieldBegin("id", ::apache::thrift::protocol::T_STRING, 1);
  xfer += oprot->writeString(this->id);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldBegin("ip", ::apache::thrift::protocol::T_STRING, 2);
  xfer += oprot->writeString(this->ip);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldBegin("port", ::apache::thrift::protocol::T_I32, 3);
  xfer += oprot->writeI32(this->port);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldStop();
  xfer += oprot->writeStructEnd();
  return xfer;
}

void swap(NodeID &a, NodeID &b) {
  using ::std::swap;
  swap(a.id, b.id);
  swap(a.ip, b.ip);
  swap(a.port, b.port);
  swap(a.__isset, b.__isset);
}

NodeID::NodeID(const NodeID& other6) {
  id = other6.id;
  ip = other6.ip;
  port = other6.port;
  __isset = other6.__isset;
}
NodeID& NodeID::operator=(const NodeID& other7) {
  id = other7.id;
  ip = other7.ip;
  port = other7.port;
  __isset = other7.__isset;
  return *this;
}
void NodeID::printTo(std::ostream& out) const {
  using ::apache::thrift::to_string;
  out << "NodeID(";
  out << "id=" << to_string(id);
  out << ", " << "ip=" << to_string(ip);
  out << ", " << "port=" << to_string(port);
  out << ")";
}

