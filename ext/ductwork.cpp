#include "ductwork.h"

#ifdef _WIN32
  // TODO: wdoze
#else
  #include <sys/stat.h>
  #include <sys/types.h>
  #include <string.h>
#endif

using Napi::String;
using Napi::Object;
using Napi::Env;
using Napi::CallbackInfo;
using Napi::Function;
using Napi::TypeError;
using Napi::Error;
using namespace Ductwork;

const mode_t MKFIFO_PERMS = 666; // TODO: mkfifo permissions

Object Ductwork::Init(Env env, Object exports) {
  exports.Set("create", Function::New(env, Create)); 
  return exports;
}

String Ductwork::Create(const CallbackInfo &info) {
  Env env = info.Env();

  if (info.Length() != 1 || !info[0].IsString()) {
    TypeError::New(env, "A single string was expected")
      .ThrowAsJavaScriptException();
  }

  String nPath = info[0].As<String>();
  std::string path = std::string(nPath);

  // TODO: check if path already exists

#ifdef _WIN32
  // TODO: wdoze
#else
  int result = mkfifo(path.c_str(), MKFIFO_PERMS);

  if (result < 0) {
    char *error = strerror(result);
    std::string message("Couldn't mkfifo: "); // TODO: better error message
    message += error;
    Error::New(env, message).ThrowAsJavaScriptException();
  }

  return nPath;
#endif
}
