#include <windows.h>
#include "ductwork.h"

using Napi::Env;
using std::string;
using namespace Win;

const char *PATH_PREFIX = "/./pipe";
const DWORD OPEN_MODE = PIPE_ACCESS_DUPLEX;
const DWORD PIPE_MODE = PIPE_TYPE_BYTE;
const DWORD MAX_INSTANCES = PIPE_UNLIMITED_INSTANCES;
const DWORD OUT_SIZE = 512;
const DWORD IN_SIZE = 512;
const DWORD TIMEOUT = 0;

const SECURITY_ATTRIBUTES SECURITY_ATTRS = {
  0,
  NULL,
  TRUE
};

Ductwork::Ductwork(Napi env, string path) : DwBase(env, path) { }

string Ductwork::Create() {
  std::string actualPath(PATH_PREFIX);
  actualPath += path;

  HANDLE handle = CreateNamedPipe(
    path.c_str(),
    OPEN_MODE,
    PIPE_MODE,
    MAX_INSTANCES,
    OUT_SIZE,
    IN_SIZE,
    TIMEOUT,
    &SECURITY_ATTRS
  );

  if (handle == INVALID_HANDLE_VALUE) {
    DWORD error = GetLastError();
    LPTSTR errorText = NULL;

    FormatMessage(
      FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_IGNORE_INSERTS,  
      NULL,
      error,
      MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
      &errorText,
      0,
      NULL
    );

    LocalFree(errorText);

    std::string message("Couldn't CreateNamedPipeA: ");
    message += std::to_string(error);
    // TODO: chuck a win32 'nana
  }

  return message.c_str();
}

void Ductwork::Read(void (*callback)(int dataLength)) {
  
}
