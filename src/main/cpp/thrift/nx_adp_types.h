/**
 * Autogenerated by Thrift Compiler (0.13.0)
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
#ifndef nx_adp_TYPES_H
#define nx_adp_TYPES_H

#include <iosfwd>

#include <thrift/Thrift.h>
#include <thrift/TApplicationException.h>
#include <thrift/TBase.h>
#include <thrift/protocol/TProtocol.h>
#include <thrift/transport/TTransport.h>

#include <functional>
#include <memory>




class XNAdpException;

typedef struct _XNAdpException__isset {
  _XNAdpException__isset() : code(false), reason(false) {}
  bool code :1;
  bool reason :1;
} _XNAdpException__isset;

class XNAdpException : public ::apache::thrift::TException {
 public:

  XNAdpException(const XNAdpException&);
  XNAdpException& operator=(const XNAdpException&);
  XNAdpException() : code(0), reason() {
  }

  virtual ~XNAdpException() noexcept;
  int32_t code;
  std::string reason;

  _XNAdpException__isset __isset;

  void __set_code(const int32_t val);

  void __set_reason(const std::string& val);

  bool operator == (const XNAdpException & rhs) const
  {
    if (!(code == rhs.code))
      return false;
    if (!(reason == rhs.reason))
      return false;
    return true;
  }
  bool operator != (const XNAdpException &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const XNAdpException & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

  virtual void printTo(std::ostream& out) const;
  mutable std::string thriftTExceptionMessageHolder_;
  const char* what() const noexcept;
};

void swap(XNAdpException &a, XNAdpException &b);

std::ostream& operator<<(std::ostream& out, const XNAdpException& obj);



#endif
