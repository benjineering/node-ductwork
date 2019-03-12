#include <sys/stat.h>
#include "fifo.h"

using std::string;
using namespace Ductwork::Nix;

Fifo::Fifo(string path) 
: file(0), path(path) { }

Fifo::Fifo(int file, string path) 
: file(file), path(path) { }

void Fifo::create(mode_t mode) {
  file = mkfifo(path.c_str(), mode);

  if (!file) {
    // throw err
  }
}

void Fifo::open() {
  if (isOpen()) {
    // throw err
  }

  // TODO
}

void Fifo::write(const char *buf, size_t len) {
  // TODO
}

bool Fifo::isOpen() {
  return this->file;
}
