
BUILD=build


if [ -d "$BUILD" ]; then
    pushd build
else
    mkdir build && pushd build && cmake ..
fi
    

cmake --build .
popd
./build/pebbleSort
