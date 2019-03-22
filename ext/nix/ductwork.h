#ifndef _WIN32

#include "../dw_base.h"
#include <napi.h>
#include <sys/select.h>

namespace Nix {
  class Ductwork : public DwBase {
  public:
    Ductwork(Napi::Env env, std::string path);
    std::string Create();
    Napi::Promise Read(char **buffer, size_t bufferSize, bool *timedOut);

  private:
    int fd;
    fd_set set;
    Napi::Promise::Deferred *promise; // TODO: delete this
  };
}

#endif
