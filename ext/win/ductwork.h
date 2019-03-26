#ifdef _WIN32

#ifndef WIN_DW
#define WIN_DW

#include "../dw_base.h"
#include <napi.h>

namespace Win {
  class Ductwork : public DwBase {
  public:
    Ductwork(Napi::Env env, std::string path);
    std::string Create();
    Napi::Promise Read(char **buffer, size_t bufferSize, bool *timedOut);
  };
}

#endif
#endif
