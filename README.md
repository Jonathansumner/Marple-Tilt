## Image To Go Here along with links to social media

Welcome to Marple Tilt, the revoluntionary new take on the popular childrens game Labrinth. This repository contains the code for both the Map Maker App and the Game System, both of which have been developed using C++. The Game is designed to run on a Raspberry Pi system and utilises an AdaFruit 64x64 Matrix and an MPU6050 Gyroscope.

## Building the Map Maker App

To be completed by Ali

## Building the Game System

The project is built using CMake and multiple helper scripts are provided to get the game up and running. The first thing you need to do is download the repository from GitHub onto your Raspberry Pi. This can be done using the following command:

```
git clone https://github.com/Jonathansumner/Marple-Tilt --recursive
```

The recursive flag is required in order to also download all submodules of the project as they are required for build the executable.

After the repository is installed you must enter the game-runner directory and execute the setup script.

```
cd Marple-Tilt/game-runner
./setup.sh
```

This will install all the required dependancies as well as building the led matrix api. This is built separately as it does not use CMake for building. The next step is to build the the executable which is done using the build script.

```
./build.sh
```

This script configures the CMake files and then runs the generated makefile which builds the executable. The code can now be ran using the command:

```
./out/build/MarpleTilt
```

To make changes to the game, simply edit the required files and then run the build script again to generate a new executable.