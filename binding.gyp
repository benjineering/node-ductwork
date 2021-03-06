{
  "targets": [
    {
      "target_name": "ductwork",
      "cflags!": [ "-fno-exceptions" ],
      "cflags_cc!": [ "-fno-exceptions" ],
      "sources": [
        "ext/index.cpp",
        "ext/wrapper.cpp",
        "ext/dw_base.cpp",
        "ext/nix/ductwork.cpp",
        "ext/win/ductwork.cpp"
      ],
      "include_dirs": [
        "<!@(node -p \"require('node-addon-api').include\")"
      ],
      "libraries": [],
      "dependencies": [
        "<!(node -p \"require('node-addon-api').gyp\")"
      ],
      "defines": [ "NAPI_DISABLE_CPP_EXCEPTIONS" ]
    }
  ]
}
