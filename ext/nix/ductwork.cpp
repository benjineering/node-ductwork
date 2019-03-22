#include <fcntl.h>
#include <sys/stat.h>
#include <thread>
#include <unistd.h>
#include "ductwork.h"

using std::string;
using std::thread;
using Napi::Env;
using Napi::Promise;
using namespace Nix;

const mode_t CREATE_PERMS = S_IRUSR | S_IWUSR;
const mode_t READ_PERMS = S_IRUSR | O_RDONLY;
const mode_t WRITE_PERMS = S_IWUSR | O_WRONLY;

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

Promise Ductwork::Read(char **buffer, size_t bufferSize, bool *timedOut) {
  promise = new Promise::Deferred(env);
  *timedOut = false;

  if (fd) {
    throwError("File already open");
  }

  printf("open started\n");

  printf("open done\n");

  if (fd < 0) {
    throwError("Error opening file");
  }

  size_t readResult = read(fd, *buffer, bufferSize);

  printf("read done\n");

  if (!readResult) {
    throwError("Error reading file");
  }

  close(fd);
  fd = 0;
  return readResult;
}
