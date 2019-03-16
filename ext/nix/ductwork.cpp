#include <fcntl.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>
#include "ductwork.h"

using std::string;
using Napi::Env;
using namespace Nix;

const mode_t CREATE_PERMS = S_IRUSR | S_IWUSR;
const mode_t READ_PERMS = S_IRUSR | O_RDONLY;
const mode_t WRITE_PERMS = S_IWUSR | O_WRONLY;
timeval SELECT_TIMEOUT { 5, 0 }; // 5 secs

Ductwork::Ductwork(Env env, string path) 
: DwBase(env, path) {
  fd = 0;
}

string Ductwork::Create() {
  int result = mkfifo(path.c_str(), CREATE_PERMS);

  if (result < 0)
    throwCreateError(path, strerror(result));

  return path;
}

void Ductwork::Read(void (*callback)(int dataLength)) {
  if (fd) {
    // TODO: handle file already open
  }

  fd = open(path.c_str(), READ_PERMS);

  if (fd == -1) {
    // TODO: throw open error
  }

  FD_SET(fd, &set);
  int nfds = fd + 1;

  // TODO: watch for exceptions?

  int result = select(nfds, &set, NULL, NULL, &SELECT_TIMEOUT);

  if (result == -1) {
    // TODO: throw watch error
  }

  bool haveData = result && FD_ISSET(fd, &set);
  callback(haveData);
}
