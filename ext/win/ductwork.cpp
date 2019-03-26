#ifdef _WIN32

#include <windows.h>
#include <strsafe.h>
#include <clocale>
#include "ductwork.h"

using Napi::Env;
using std::string;
using std::setlocale;
using std::function;

using namespace Win;

const char *PATH_PREFIX = "//./pipe";
const DWORD OPEN_MODE = PIPE_ACCESS_DUPLEX;
const DWORD PIPE_MODE = PIPE_TYPE_BYTE;
const DWORD MAX_INSTANCES = PIPE_UNLIMITED_INSTANCES;
const DWORD OUT_SIZE = 512;
const DWORD IN_SIZE = 512;
const DWORD TIMEOUT = 0;

SECURITY_ATTRIBUTES SECURITY_ATTRS = {
  0,
  NULL,
  TRUE
};

Ductwork::Ductwork(Env env, string path) : DwBase(env, path) { }

string Ductwork::Create() {
  std::string actualPath(PATH_PREFIX);
  actualPath += path;

  setlocale(LC_ALL, "en_US.utf8"); // TODO: get locale 
  size_t pathLen = actualPath.size() + 1;
  LPTSTR cPath = (LPTSTR)malloc(sizeof(TCHAR) * pathLen);
  mbstowcs((wchar_t *)cPath, actualPath.c_str(), pathLen);

  HANDLE handle = CreateNamedPipe(
    cPath,
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
    LPVOID errorText;

    FormatMessage(
      FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_IGNORE_INSERTS,  
      NULL,
      error,
      MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
      (LPTSTR)&errorText,
      0,
      NULL
    );


    //std::string message("Couldn't CreateNamedPipeA: ");
    //message += errorText;
    // TODO: chuck a win32 'nana

    printf("Couldn't create named pipe '%ls': %ld = ", cPath, error);
    wprintf(L"%ls\n", (wchar_t *)errorText);

    LocalFree(errorText);
    free(cPath);
  }

  return actualPath.c_str();
}

void Ductwork::Read(char **buffer, size_t length, std::function<void(int len, bool timeout)> callback) {
  
}

#endif
