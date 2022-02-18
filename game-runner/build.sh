#! /bin/sh

make -C external/matrix-api
make -C external/mpu6050-api

cmake -S . -B out/build

make -C out/build