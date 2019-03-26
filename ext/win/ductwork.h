#ifdef _WIN32

#ifndef WIN_DW_H
#define WIN_DW_H

#include "../dw_base.h"
#include <napi.h>

namespace Win {
  class Ductwork : public DwBase {
  public:
    Ductwork(Napi::Env env, std::string path);
    std::string Create();
    void Read(char **buffer, size_t length, std::function<void(int len, bool timeout)> callback);
  };
}

#endif
#endif
