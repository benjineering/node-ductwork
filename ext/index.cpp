#include <napi.h>
#include "ductwork.h"

using Napi::Object;
using Napi::Env;

Object InitAll(Env env, Object exports) {
  return Ductwork::Init(env, exports);
}

NODE_API_MODULE(ductwork, InitAll)
