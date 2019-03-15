#include "dw_base.h"

using Napi::Env;
using Napi::Error;
using std::string;

DwBase::DwBase(Env env, string path) : env(env), path(path) { }

void DwBase::throwError(string message) {
  // TODO: different error types?
  Error::New(env, message).ThrowAsJavaScriptException();
}
