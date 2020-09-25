# wasm-sdl-tinkering

Quick repo to play with WASM & SDL2

## Installation
### Emscripten
To compile with emscripten, (install it here https://emscripten.org/docs/getting_started/index.html), then run this in the root folder

`./compile_emscripten.sh`
### C++
To run with C++

install vcpkg via github

`./vcpkg integrate install`

`./vcpkg install sdl2 sdl2-image`

Set env to wherever you installed VCPKG

`VCPKG_ROOT=`

Alternatively use `example.settings.json` to specify vcpkg cmake toolchain file (if you accidentally do this after cmake: configure, you'll have to run cleanup.sh and go again)

use suggested vs code extensions to run via cmake (Shift+CMD+P "Cmake: Configure")

To clear out temporary files locally run this, (sometimes required if messing w/new libs)

`./cleanup.sh`

When adding new `.h` & `.cpp` files, ensure to go back into CMakeLists.txt, add a space + hit save. That'll auto add new files to the build.

When setting up environment for first time, please download suggested VSCode plugins, and ensure you've setup this one `jbenden.c-cpp-flylint` (including installing system dependencies) and have `config.formatOnSave` equal to true. This ensures auto-linter stays working

## Goal
Build a game sandbox application that cross-compiles to WASM, MacOS, & Linux Desktop

## TODO
* Port some generic components I built in college to be WASM-compatible
  * Generic Asset Loading
  * Audio
  * 2D Animation
  * Controller + Keyboard input
* Get Fullscreen properly working in browser (kinda works but iffy right now)
* Split Code into Framework v Implementation
  * I want a monolithic application that can hot-load / unload new scenes 1 by 1
  * Each scene will start as an empty sandbox app, with access to common framework components. Each scene will be used to spike new ideas/libraries/gameplay prototypes etc.
  * Each scene will be loadable via an IMGUI ui scene picker
* Build a CD pipeline for repo
  * auto compile and deploy the monolithic sandbox application to an S3 bucket (behind a CDN) on every push to master
  *  Make accessible to a domain so I can access it easily for demo purposes.