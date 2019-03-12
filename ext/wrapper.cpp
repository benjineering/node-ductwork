#include "wrapper.h"
#include "nix/fifo.h"

using v8::FunctionCallbackInfo;
using v8::Value;
using v8::Local;
using v8::Object;
using v8::Persistent;
using v8::Function;
using namespace Ductwork;
using namespace Ductwork::Nix;

Persistent<Function> Wrapper::constructor;

void Wrapper::Init(Local<Object> exports) {
  
}

void Wrapper::New(const FunctionCallbackInfo<Value>& args) {
  std::string path;
  Fifo *fifo;
  int numArgs = args.Length();

  if (!args.IsConstructCall()) {
    // throw err
  }
  
  if (numArgs < 1 || numArgs > 2) {
    // throw err
  }

  if (!args[0]->IsString()) {
    // throw err
  }

  path = std::string(*v8::String::Utf8Value(args[0]->ToString()));

  if (numArgs == 1) {
    fifo = new Fifo(path);
  }
  else {
    // TODO
  }

  Wrap(args.This());
  args.GetReturnValue().Set(args.This());
}
