# wasm-sdl-tinkering
Quick repo to play with WASM & SDL2

- To compile with emscripten, (install it here https://emscripten.org/docs/getting_started/index.html), then run this
`emcc main.cpp -s WASM=1 -s USE_SDL=2 -O3 -o dist/index.js --preload-file assets/sample.bmp`

- To run with C++

install vcpkg via github
-
`./vcpkg integrate install`
`./vcpkg install sdl2-image`
`./vcpkg install sdl2`


Set env to wherever you installed VCPKG
`VCPKG_ROOT=`

Alternatively use `example.settings.json` to specify vcpkg cmake

use suggested vs code extensions to run via cmake
