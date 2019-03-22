#include "wrapper.h"

#ifdef _WIN32
  #include "win/ductwork.h"
  using Win::Ductwork;
#else
  #include "nix/ductwork.h"
  using Nix::Ductwork;
#endif

using Napi::String;
using Napi::Object;
using Napi::Env;
using Napi::CallbackInfo;
using Napi::Function;
using Napi::TypeError;
using Napi::Error;
using Napi::Value;
using Napi::Promise;
using Napi::Number;

/*
 *  TODO: sort out object wrapping
 */
Ductwork *dw;
const size_t BUFFER_SIZE = 512;
char *buffer = (char *)malloc(BUFFER_SIZE);

Object Wrapper::Init(Env env, Object exports) {
  exports.Set("create", Function::New(env, Create));
  exports.Set("readStringSync", Function::New(env, ReadStringSync));
  return exports;
}

String Wrapper::Create(const CallbackInfo &info) {
  Env env = info.Env();

  if (info.Length() != 1 || !info[0].IsString()) {
    TypeError::New(env, "A single string was expected")
      .ThrowAsJavaScriptException();
  }

  String nPath = info[0].As<String>();
  std::string path = std::string(nPath);

  dw = new Ductwork(env, path);
  std::string actualPath = dw->Create();

  return String::New(env, actualPath);
}

Value Wrapper::ReadStringSync(const CallbackInfo &info) {
  Env env = info.Env();
  bool timedOut;
  int length = dw->Read(&buffer, BUFFER_SIZE, &timedOut);

  if (timedOut) {
    return Value::From(env, NULL);
  }
  else {
    return String::New(env, buffer, length);
  }
}
