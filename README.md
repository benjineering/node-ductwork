# node-ductwork
Cross platform FIFO pipes for node

### TODO
- General concept
  - Ensure open() doesn't block child threads or processes so it's possible to
    call a blocking open() from Node and wait on it's Promise...?
- Tests
  -  Whens (aka context)
- C
  - Write DW in pure C
  - Pass Napi::Env around as user data
  - Encapsulate state properly in wrapper
- Timeout
  - Probably a second thread that calls deferred.fail() after some time
