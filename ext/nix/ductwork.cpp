#ifndef _WIN32

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

string OpenAsync(
  const char *path,
  char **buffer,
  size_t length,
  void (*callback)(int len, bool timeout)
) {
  printf("open started\n");

  int fd = open(path, READ_PERMS);

  printf("open done\n");

  if (fd < 0)
    return "Error opening file";

  size_t readResult = read(fd, *buffer, length);

  printf("read done\n");

  if (!readResult)
    return "Error reading file";

  close(fd);
  fd = 0;
    
  printf("file closed\n");

  (*callback)(readResult, false);
  return "";
}

Ductwork::Ductwork(Env env, string path) 
: DwBase(env, path) { }

string Ductwork::Create() {
  int result = mkfifo(path.c_str(), CREATE_PERMS);

  if (result < 0)
    throwCreateError(path, strerror(result));

  return path;
}

void Ductwork::Read(
  char **buffer,
  size_t length,
  void (*callback)(int len, bool timeout)
) {
  openThread = new thread(
    OpenAsync,
    path.c_str(),
    buffer,
    length,
    callback
  );

  openThread->join();
}

#endif
