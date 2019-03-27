#ifdef _WIN32

#include <clocale>
#include "ductwork.h"

using Napi::Env;
using std::string;
using std::setlocale;
using std::thread;

using namespace Win;

const char *PATH_PREFIX = "//./pipe";
const DWORD OPEN_MODE = PIPE_ACCESS_DUPLEX;
const DWORD PIPE_MODE = PIPE_WAIT;
const DWORD MAX_INSTANCES = PIPE_UNLIMITED_INSTANCES;
const DWORD OUT_SIZE = 512;
const DWORD IN_SIZE = 512;
const DWORD TIMEOUT_MS = 2000; // 2 secs

string OpenAsync(
  const char *path,
  char **buffer,
  size_t length,
  void (*callback)(int len, bool timeout)
) {
  DWORD readResult;
  bool timeout = false;

  bool success = CallNamedPipeA(
    path,
    NULL,
    0,
    buffer,
    length,
    &readResult,
    NMPWAIT_USE_DEFAULT_WAIT
  );

  if (!success) {
    DWORD error = GetLastError();

    if (error == ERROR_SEM_TIMEOUT)
      timeout = true;
    //else TODO: throw error
  }

  (*callback)(readResult, success);
  return "";
}

Ductwork::Ductwork(Env env, string path) : DwBase(env, path) { }

string Ductwork::Create() {
  fullPath = string(PATH_PREFIX);
  fullPath += path;

  HANDLE handle = CreateNamedPipeA(
    fullPath.c_str(),
    OPEN_MODE,
    PIPE_MODE,
    MAX_INSTANCES,
    OUT_SIZE,
    IN_SIZE,
    TIMEOUT_MS,
    NULL
  );

  if (handle == INVALID_HANDLE_VALUE) {
    DWORD error = GetLastError();
    LPSTR errorText;

    FormatMessageA(
      FORMAT_MESSAGE_FROM_SYSTEM | 
        FORMAT_MESSAGE_IGNORE_INSERTS | 
        FORMAT_MESSAGE_ALLOCATE_BUFFER,  
      NULL,
      error,
      MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
      (LPSTR)&errorText,
      0,
      NULL
    );

    // TODO: throw error
    printf("Couldn't create named pipe '%s': %s", fullPath, (char *)errorText);

    free(errorText);
  }

  return fullPath.c_str();
}

void Ductwork::Read(char **buffer, size_t length, void (*callback)(int len, bool timeout)) {
  openThread = new thread(
    OpenAsync,
    fullPath.c_str(),
    buffer,
    length,
    callback
  );
}

#endif
