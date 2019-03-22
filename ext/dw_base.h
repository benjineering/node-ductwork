#include <string>
#include <napi.h>

class DwBase {
public:
  DwBase(Napi::Env env, std::string path);
  virtual std::string Create() = 0;
  virtual Napi::Promise Read(char **buffer, size_t bufferSize, bool *timedOut) = 0;
  
protected:
  Napi::Env env;
  std::string path;
  void throwError(std::string message);
  void throwCreateError(std::string actualPath, std::string reason);
};
