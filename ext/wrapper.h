#ifndef DW_WRAPPER_H
#define DW_WRAPPER_H

#include <node.h>
#include <node_object_wrap.h>

namespace Ductwork {
  namespace Nix {
    class Fifo;
  }

  class Wrapper : public node::ObjectWrap {
  public:
    static void Init(v8::Local<v8::Object> exports);
    void New(const v8::FunctionCallbackInfo<v8::Value>& args);

  private:
    static v8::Persistent<v8::Function> constructor;
  };
}

#endif
