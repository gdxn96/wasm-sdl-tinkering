emcc main.cpp -s USE_SDL=2 -s USE_SDL_IMAGE=2 -s SDL2_IMAGE_FORMATS='["png"]' -O3 -o dist/index.js  --preload-file assets
# cp assets/** dist/assets/