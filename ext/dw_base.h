#include <string>
#include <napi.h>

class DwBase {
public:
  DwBase(Napi::Env env, std::string path);
  virtual std::string Create() = 0;
  virtual void Read(void (*callback)(int dataLength)) = 0;
  static const int READ_BUFFER_SIZE = 512;
  
protected:
  Napi::Env env;
  std::string path;
  char buffer[READ_BUFFER_SIZE];
  void throwError(std::string message);
  void throwCreateError(std::string actualPath, std::string reason);
};
