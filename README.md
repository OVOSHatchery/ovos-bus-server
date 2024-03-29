# OVOS Bus Server

Alternative C++ messagebus server implementation for ovos-core using
the [WebSocket++](https://github.com/zaphoyd/websocketpp) WebSocket library.

## Dependencies

The following libraries are bundled in the source tree, under the `server/external` directory:

- [WebSocket++](https://github.com/zaphoyd/websocketpp)
- [Asio](http://think-async.com/)
- [JsonCpp](https://github.com/open-source-parsers/jsoncpp)

When compiling under MinGW, [Boost.Thread](http://www.boost.org/doc/libs/release/libs/thread/) is also required, due to
a bug in MinGW that prevents WebSocket++ from using C++11 functionality alone (
see [this StackOverflow post](http://stackoverflow.com/questions/33662788/undefined-reference-to-stderrcoperation-canceled-when-compiling-websocketp)
for details.)

## Building the server

Building the server requires a recent version of the [CMake](https://cmake.org/) build system. To build the server,
invoke the following commands in the `server` directory:

```
cmake .
cmake --build .
```

When compiling with Visual Studio under Windows, these command need to be run from the _"Visual Studio Native Tools
Command Prompt"_, which includes the neccessary build tools in the `PATH`.

## License

The bundled libraries are each covered by their own licenses:

- WebSocket++ - **BSD 3-Clause License** (see `server/external/LICENSE/websocketpp.txt`)
- Asio - **Boost Software License** (see `server/external/LICENSE/asio.txt`)
- JsonCpp - **Public Domain / MIT License** (see `server/external/LICENSE/jsoncpp.txt`)

All of the remaining code is licensed under the MIT License. See the file `LICENSE` for details.

## Credits

Based of https://github.com/adamrehn/websocket-server-demo
