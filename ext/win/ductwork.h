#ifdef _WIN32

#include "../dw_base.h"
#include <napi.h>

namespace Win {
  class Ductwork : public DwBase {
  public:
    Ductwork(Napi::Env env, std::string path);
    std::string Create();
  };
}

#endif
