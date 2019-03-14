#include "../dw_base.h"

namespace Nix {
  class Ductwork : public DwBase {
  public:
    Ductwork(std::string path);
    std::string Create();
  };
}
