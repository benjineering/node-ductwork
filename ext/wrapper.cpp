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
Promise::Deferred *deferredRead;
Env *oneEnv;

Object Wrapper::Init(Env env, Object exports) {
  exports.Set("create", Function::New(env, Create));
  exports.Set("readString", Function::New(env, ReadString));
  return exports;
}

String Wrapper::Create(const CallbackInfo &info) {
  Env env = info.Env();

  if (info.Length() != 1 || !info[0].IsString())
    TypeError::New(env, "A single string was expected")
      .ThrowAsJavaScriptException();

  String nPath = info[0].As<String>();
  std::string path = std::string(nPath);

  dw = new Ductwork(env, path);
  std::string actualPath = dw->Create();

  return String::New(env, actualPath);
}

void ReadCallback(int len, bool timeout) {
  if (timeout)
    deferredRead->Reject(Value::From(*oneEnv, "Timed out"));
  else
    deferredRead->Resolve(Value::From(*oneEnv, "promise is working"));
}

Value Wrapper::ReadString(const CallbackInfo &info) {
  *oneEnv = info.Env();
  deferredRead = new Promise::Deferred(*oneEnv);
  dw->Read(&buffer, BUFFER_SIZE, ReadCallback);
  return deferredRead->Promise();
}

