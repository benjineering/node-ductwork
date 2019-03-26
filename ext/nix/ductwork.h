#ifndef _WIN32

#ifndef NIX_DW_H
#define NIX_DW_H

#include "../dw_base.h"
#include <sys/select.h>
#include <thread>

namespace Nix {
  class Ductwork : public DwBase {
  public:
    Ductwork(Napi::Env env, std::string path);
    std::string Create();
    void Read(char **buffer, size_t length, void (*callback)(int len, bool timeout));

  private:
    int fd;
    std::thread *openThread; // TODO: free this
  };
}

#endif
#endif
