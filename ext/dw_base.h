#ifndef DW_BASE_H
#define DW_BASE_H

#include <string>
#include <napi.h>

class DwBase {
public:
  DwBase(Napi::Env env, std::string path); // TODO: pass error callback instead of env
  virtual std::string Create() = 0;
  virtual void Read(char **buffer, size_t length, void (*callback)(int len, bool timeout)) = 0;
  
protected:
  Napi::Env env;
  std::string path;
  void throwError(std::string message);
  void throwCreateError(std::string actualPath, std::string reason);
};

#endif
