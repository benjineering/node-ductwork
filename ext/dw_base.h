#include <string>

class DwBase {
public:
  DwBase(std::string path);
  virtual std::string Create() = 0;
  
protected:
  std::string path;
};
