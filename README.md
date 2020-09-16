# wasm-sdl-tinkering
Quick repo to play with WASM & SDL2

To compile with emscripten, (install it here https://emscripten.org/docs/getting_started/index.html), then run this

`./compile_emscripten.sh`

To run with C++

install vcpkg via github

`./vcpkg integrate install`

`./vcpkg install sdl2-image`

`./vcpkg install sdl2`


Set env to wherever you installed VCPKG

`VCPKG_ROOT=`

Alternatively use `example.settings.json` to specify vcpkg cmake

use suggested vs code extensions to run via cmake (Shift+CMD+P "Cmake: Configure")

To clear out temporary files locally run this, (sometimes required if messing w/new libs)

`git clean -fdX -e \!.vscode -e \!.vscode/**`
