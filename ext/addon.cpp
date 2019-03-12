#include <napi.h>

using Napi::Object;
using Napi::Env;

Object InitAll(Env env, Object exports) {
  return exports;
}

NODE_API_MODULE(ductwork, InitAll)
