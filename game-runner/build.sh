#! /bin/sh

sudo apt-get update

# Install MPU6050 dependencies
sudo apt-get install libi2c-dev i2c-tools libi2c0

# Install RGB Matrix dependencies
sudo apt-get install libgraphicsmagick++-dev libwebp-dev -y

# Build RGB Matrix and MPU6050 projects
make -C external/matrix-api
make -C external/mpu6050-api

# Configure Marple Tilt project
cmake --no-warn-unused-cli -DCMAKE_TOOLCHAIN_FILE=cross.cmake -DCMAKE_EXPORT_COMPILE_COMMANDS:BOOL=TRUE -DCMAKE_BUILD_TYPE:STRING=Debug -B out/build -G "Unix Makefiles"

# Build Marple Tilt project
make -C out/build