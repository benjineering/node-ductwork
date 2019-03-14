#include "../dw_base.h"

namespace Win {
  class Ductwork : public DwBase {
  public:
    Ductwork(std::string path);
    std::string Create();
  };
}
