#include <napi.h>
#include "wrapper.h"

using Napi::Object;
using Napi::Env;

Object InitAll(Env env, Object exports) {
  return Wrapper::Init(env, exports);
}

NODE_API_MODULE(ductwork, InitAll)
