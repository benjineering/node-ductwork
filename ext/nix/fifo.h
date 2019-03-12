#ifndef DW_NIX_FIFO_H
#define DW_NIX_FIFO_H

#include <string> 
#include <fcntl.h>

namespace Ductwork {
  namespace Nix {    
    class Fifo {
    public:
      Fifo(std::string path);
      Fifo(int file, std::string path);
      void create(mode_t mode = O_RDONLY);
      void open();
      void write(const char *buf, size_t len);
      bool isOpen();
    private:
      int file;
      std::string path;
    };
  }
}

#endif
