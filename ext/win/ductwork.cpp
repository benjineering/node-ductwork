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
  LPTSTR path,
  char **buffer,
  size_t length,
  void (*callback)(int len, bool timeout)
) {
  DWORD readResult;
  bool timeout = false;

  bool success = CallNamedPipe(
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
  std::string actualPath(PATH_PREFIX);
  actualPath += path;

  setlocale(LC_ALL, "en_US.utf8"); // TODO: get locale 
  size_t pathLen = actualPath.size() + 1;
  widePath = (LPTSTR)malloc(sizeof(TCHAR) * pathLen);
  mbstowcs((wchar_t *)widePath, actualPath.c_str(), pathLen);

  HANDLE handle = CreateNamedPipe(
    widePath,
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
    printf("Couldn't create named pipe '%ls': %s", widePath, (char *)errorText);

    free(errorText);
  }

  return actualPath.c_str();
}

void Ductwork::Read(char **buffer, size_t length, void (*callback)(int len, bool timeout)) {
  openThread = new thread(
    OpenAsync,
    widePath,
    buffer,
    length,
    callback
  );
}

#endif
