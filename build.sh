#!/usr/bin/env bash
if [ ! -d "build" ]; then
    mkdir build
    cd build
    cmake .. -DTARGET_MINGW32=ON
    cd ..
fi
cd build
cmake .. -DTARGET_MINGW32=ON
make