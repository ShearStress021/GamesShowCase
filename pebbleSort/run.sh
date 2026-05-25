
BUILD=build


if [ -d "$BUILD" ]; then
    cd build
else
    mkdir build && cd build && cmake ..
fi
    

cmake --build .
./pebbleSort/pebbleSort
