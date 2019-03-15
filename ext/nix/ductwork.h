#include "../dw_base.h"
#include <napi.h>

namespace Nix {
  class Ductwork : public DwBase {
  public:
    Ductwork(Napi::Env env, std::string path);
    std::string Create();
  };
}
