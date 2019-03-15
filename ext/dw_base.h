#include <string>
#include <napi.h>

class DwBase {
public:
  DwBase(Napi::Env env, std::string path);
  virtual std::string Create() = 0;
  
protected:
  Napi::Env env;
  std::string path;
  void throwError(std::string message);
};
