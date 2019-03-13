#include "ductwork.h"

// TODO: make constants overridable

#ifdef _WIN32
  #include <windows.h>
  const char *PATH_PREFIX = "/./pipe";
  const DWORD OPEN_MODE = PIPE_ACCESS_DUPLEX;
  const DWORD PIPE_MODE = PIPE_TYPE_BYTE;
  const DWORD MAX_INSTANCES = PIPE_UNLIMITED_INSTANCES;
  const DWORD OUT_SIZE = 512;
  const DWORD IN_SIZE = 512;
  const DWORD TIMEOUT = 0;
  SECURITY_ATTRIBUTES SECURITY_ATTRS = {
    0,
    NULL,
    TRUE
  };
#else
  #include <sys/stat.h>
  #include <sys/types.h>
  #include <string.h>
  const mode_t MKFIFO_PERMS = 666;
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
using namespace Ductwork;

Object Ductwork::Init(Env env, Object exports) {
  exports.Set("create", Function::New(env, Create));
  exports.Set("wait", Function::New(env, Wait));
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

  // TODO: move platforms off-world

#ifdef _WIN32
  std::string actualPath(PATH_PREFIX);
  actualPath += path;

  HANDLE handle = CreateNamedPipe(
    path.c_str(),
    OPEN_MODE,
    PIPE_MODE,
    MAX_INSTANCES,
    OUT_SIZE,
    IN_SIZE,
    TIMEOUT,
    &SECURITY_ATTRS
  );

  if (handle == INVALID_HANDLE_VALUE) {
    DWORD error = GetLastError();
    LPTSTR errorText = NULL;

    FormatMessage(
      FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_IGNORE_INSERTS,  
      NULL,
      error,
      MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
      &errorText,
      0,
      NULL
    );

    LocalFree(errorText);

    std::string message("Couldn't CreateNamedPipeA: ");
    message += std::to_string(error);
    Error::New(env, message).ThrowAsJavaScriptException();
  }

  return String::New(env, actualPath);
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

Value Ductwork::Wait(const CallbackInfo &info) {
  Promise::Deferred deferred = Promise::Deferred::New(info.Env());
  // TODO: select()
  // TODO: win32 WaitNamedPipe
  return deferred.Promise();
}
