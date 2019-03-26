#include <napi.h>
#include "wrapper.h"

#define UNICODE 1
#define _UNICODE 1

using Napi::Object;
using Napi::Env;

Object InitAll(Env env, Object exports) {
  return Wrapper::Init(env, exports);
}

NODE_API_MODULE(ductwork, InitAll)
