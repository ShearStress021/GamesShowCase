#!/bin/bash -

BUILD="build"

if [ -d "$BUILD" ] ; then
	echo "Directory $BUILD  exists"
	cd build && make && cd ..
else
	mkdir build && cd build && cmake .. && make && cd ..

fi
./build/res
