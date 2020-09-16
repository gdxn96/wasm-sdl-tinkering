emcc main.cpp -s USE_SDL=2 -O3 -o dist/index.js
cp assets/** dist/assets/