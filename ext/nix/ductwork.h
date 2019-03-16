#include "../dw_base.h"
#include <napi.h>
#include <sys/select.h>

namespace Nix {
  class Ductwork : public DwBase {
  public:
    Ductwork(Napi::Env env, std::string path);
    std::string Create();
    void Read(void (*callback)(int dataLength));

  private:
    int fd;
    fd_set set;
  };
}
