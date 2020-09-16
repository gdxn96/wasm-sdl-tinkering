emcc main.cpp -s WASM=1 -s USE_SDL=2 -O3 -o dist/index.js -s SDL2_IMAGE_FORMATS='["bmp","png","xpm"]'
cp assets/** dist/assets/