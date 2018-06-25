#ifndef RPC_TYPES_H
#define RPC_TYPES_H

#include "infra/Assert.hpp"

#ifdef JITAAS_USE_GRPC
#include "grpc/StreamTypes.hpp"
#endif
#ifdef JITAAS_USE_RAW_SOCKETS
#include "raw/StreamTypes.hpp"
#endif

namespace JITaaS
{
   class StreamFailure: public virtual std::exception
      {
   public:
      StreamFailure() : _message("Generic stream failure") { }
      StreamFailure(std::string message) : _message(message) { }
      virtual const char* what() const throw() { return _message.c_str(); }
   private:
      std::string _message;
      };

   class StreamCancel: public virtual std::exception
      {
   public:
      virtual const char* what() const throw() { return "compilation canceled by client"; }
      };

   class StreamTypeMismatch: public virtual StreamFailure
      {
   public:
      StreamTypeMismatch(std::string message) : StreamFailure(message) { TR_ASSERT(false, "type mismatch"); }
      };

   class StreamArityMismatch: public virtual StreamFailure
      {
   public:
      StreamArityMismatch(std::string message) : StreamFailure(message) { TR_ASSERT(false, "arity mismatch"); }
      };

   class ServerCompFailure: public virtual std::exception
      {
   public:
      ServerCompFailure() : _message("Generic JITaaS server compilation failure") { }
      ServerCompFailure(std::string message) : _message(message) { }
      virtual const char* what() const throw() { return _message.c_str(); }
   private:
      std::string _message;
      };
}

#endif // RPC_TYPES_H
