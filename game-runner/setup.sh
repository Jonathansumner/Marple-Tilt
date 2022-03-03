#! /bin/sh

sudo apt-get update

# Install MPU6050 dependencies
sudo apt-get install libi2c-dev i2c-tools libi2c0

# Install RGB Matrix dependencies
sudo apt-get install libgraphicsmagick++-dev libwebp-dev -y

# Build RGB Matrix and MPU6050 projects
make -C external/matrix-api