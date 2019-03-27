#ifdef _WIN32

#ifndef WIN_DW_H
#define WIN_DW_H

#include "../dw_base.h"
#include <napi.h>
#include <windows.h>
#include <thread>

namespace Win {
  class Ductwork : public DwBase {
  public:
    Ductwork(Napi::Env env, std::string path);
    std::string Create();
    void Read(char **buffer, size_t length, void (*callback)(int len, bool timeout));
  private:
    std::thread *openThread;
    LPTSTR widePath; // TODO: free me
  };
}

#endif
#endif
