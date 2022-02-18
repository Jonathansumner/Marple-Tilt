#! /bin/sh

sudo apt-get install libi2c-dev
sudo apt-get install i2c-tools
sudo apt-get install libi2c0

make -C external/matrix-api
make -C external/mpu6050-api

cmake --no-warn-unused-cli -DCMAKE_TOOLCHAIN_FILE=cross.cmake -DCMAKE_EXPORT_COMPILE_COMMANDS:BOOL=TRUE -DCMAKE_BUILD_TYPE:STRING=Debug -B out/build -G "Unix Makefiles"

make -C out/build