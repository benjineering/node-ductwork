#include <sys/stat.h>
#include <sys/types.h>
#include <stdexcept>
#include "ductwork.h"

using std::string;
using namespace Nix;

const mode_t MKFIFO_PERMS = 666;

Ductwork::Ductwork(string path) : DwBase(path) { }

string Ductwork::Create() {
  int result = mkfifo(path.c_str(), MKFIFO_PERMS);

  // TODO: better errors
  if (result < 0) {
    char *error = strerror(result);
    std::string message("Couldn't mkfifo: ");
    message += error;
    throw std::runtime_error(message);
  }

  return path;
}
