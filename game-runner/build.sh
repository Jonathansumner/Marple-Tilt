#! /bin/sh

#cmake --no-warn-unused-cli -DCMAKE_TOOLCHAIN_FILE=cross.cmake -DCMAKE_EXPORT_COMPILE_COMMANDS:BOOL=TRUE -DCMAKE_BUILD_TYPE:STRING=Debug -B out/build -G "Unix Makefiles"
cmake -S . -B out/build

# Build Marple Tilt project
make -C out/build