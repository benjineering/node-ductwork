#ifndef DW_WRAPPER_H
#define DW_WRAPPER_H

#include <napi.h>
#include <string>

namespace Ductwork {
  enum WaitMode {
    READ,
    WRITE,
    READ_WRITE
  };

  Napi::Object Init(Napi::Env env, Napi::Object exports);
  Napi::String Create(const Napi::CallbackInfo &info);
}

#endif
