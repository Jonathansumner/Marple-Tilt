<p align="center">
<img width="200" src="https://github.com/Jonathansumner/Marple-Tilt/blob/main/Icons/marple_logo_resized.jpg" alt="Material Bread logo">
<h1 align="center">Marple Tilt: Don't Lose Your Marples</h1>
</p>
<p align="center">
<a href =https://www.instagram.com/marpletilt/ ><img src="https://raw.githubusercontent.com/Jonathansumner/Marple-Tilt/main/resources/icons/Instagram.png" width="64"/> </a><a href =https://www.tiktok.com/@marpletilt ><img src="https://raw.githubusercontent.com/Jonathansumner/Marple-Tilt/main/resources/icons/Tiktok.png" width="64"/> </a><a href =https://www.twitter.com/marpletilt ><img src="https://raw.githubusercontent.com/Jonathansumner/Marple-Tilt/main/resources/icons/Twitter.png" width="64"/> </a>
</p>

Welcome to Marple Tilt, the revoluntionary new take on the popular childrens game Labrinth. This repository contains the code for both the Map Maker App and the Game System, both of which have been developed using C++. The Game is designed to run on a Raspberry Pi system and utilises an AdaFruit 64x64 Matrix and an MPU6050 Gyroscope.

## Downloading the Source Code

The project is stored and maintained using GitHub so the first task is to download the source code. This can be done in two ways, by downloading the zip file or by cloning the repository onto your machine. To clone the repository, use the command:

```
git clone https://github.com/Jonathansumner/Marple-Tilt --recursive
```

The "--recursive" flag ensures that the project's submodules are downloaded as they are required to build the app.

## Building the Map Maker App

The Map Creator Application is built using CMake, C++ and Qt5. Handily both C++ and CMake come packaged with an install of Qt5 so simply go to: https://www.qt.io/download and select "Go Open Source" and download the online installer. Note: you will need to make an account with Qt during this process.

### Linux Install
While the Qt package is downloading, run the following commands in the terminal to ensure all required packages for the install are present.

```
sudo apt-get update && sudo apt-get upgrade
sudo apt-get -y install build-essential openssl libssl-dev libssl1.0 libgl1-mesa-dev libqt5x11extras5
```

Once the installer is downloaded you must first make the installer executable. Navigate to the directory it has downloaded to and run the following commands, replacing "qt*.run" with the exact name of the downloaded installer.

```
chmod +x qt*.run
./qt*.run
```

The installer should now open and ask for login credentials, after entering these you will be presented with a range of different Qt versions. Make sure to select at least version 5.15.1 and also make sure that CMake is ticked under the Tools tab. Now proceed to the download stage.

Once everything is downloaded you can now begin editing the project in either Qt Creator or in an IDE of your choice in conjunction with the command line.

#### Qt Creator

To open the project in Qt Creator simply navigate to the source code and open the "CMakeLists.txt.user" file to load the configuration. A warning will likely appear here and you be asked to reconfigure the project. Here select "Qt 5.15.1 GCC 64-bit" as the Kit. You are now ready to build and run the code!

#### Custom

To work on the project in another IDE you must build the project in the command line and this is very straighforward. In the command line navigate to the directory containing the Marple Tilt files. Here, run the command:

```
\path\to\Tools\CMake\bin\cmake -DCMAKE_PREFIX_PATH="\path\to\5.15.1\gcc_64" -S . -B out
cd out
make
```

cmake can be found in the Tools folder of the Qt installation. The CMAKE_PREFIX_PATH should be set to the location of the Qt installation within the Qt folder.

#### Running the Executable

In linux the executable can be run from the command line with the line:

```
./MapCreator
```

However if you want to run the application on a device that does not have Qt installed you will need to use a tool such as "linuxdeployqt".

### Windows Install

The install process for a Window machine is very straight forward. Simply download the installer and as mentioned, make sure at least version 5.15.1 is selected and also that CMake is selected under the tools tab. You must also make sure that Ninja and at least MinGW 8.1.0 (64-bit) install ticked.

Once everything is installed you can begin editing the project via two methods, using the Qt Creator App (which comes with Qt) or in an IDE of your choice with the command line for building.

#### Qt Creator

To open the project in Qt Creator, click "Open File or Project" and select the "CMakeLists.txt.user" file. This will load up the project however, you will need to check the build configuration and ensure that the paths to all the required files are set correctly. 

If you are having trouble with this step, open a new project and select the type Qt Console Application with Cmake selected as the build system and MinGW 64-bit selected as the Kit. Then if you go into the build configuration it will show you the correct paths which can be copied over to the Marple Tilt project you have opened. Once this is complete you should be able to build and run the project in Qt Creator.

#### Custom

To work on the project in another IDE you must build the project in the command line and this is relatively straighforward. First you must open up a MinGW command line, type "Qt 5.15.1 (MinGW 8.1.0 (64-bit))" into the windows search bar to bring up the command line (replace 8.1.0 with any newer version of MinGW).

In this command line navigate to the directory containing the Marple Tilt files. Here, run the command:

```
\path\to\Tools\CMake_64\bin\cmake.exe -DCMAKE_PREFIX_PATH="\path\to\5.15.1\mingw81_64" -G"MinGW Makefiles" -S . -B out
cd out
\path\to\Tools\mingw810_64\bin\mingw32-make.exe
```

"cmake.exe" and "mingw32-make.exe" can be found in the Tools folder of the Qt installation. The CMAKE_PREFIX_PATH should be set to the location of the Qt installation within the Qt folder.

#### Running the Executable

The generated executable can be found in the folder out. However the command:

```
windeployqt.exe --quick .
```

then needed to be run to include the required libraries for Qt. The out folder can now be zipped and placed anywhere and in any machine and it will run regardless of what is installed on that machine (as long as its a windows machine).

## Building the Game System

The project is built using CMake and multiple helper scripts are provided to get the game up and running. The first script to execute is "setup.sh" which will install all required dependencies and will also build the matrix-api (the api is build using make and not cmake and so is not fully integrated).

```
cd Marple-Tilt/game-runner
sudo ./setup.sh
```
The next step is to build the the executable which is done using the build script. This will run cmake to generate the makefile and then will run the makefile to create the executable.

```
sudo ./build.sh
```

The code can now be ran using the command:

```
sudo ./out/build/MarpleTilt
```

To make changes to the game, simply edit the required files and then run the build script again to generate a new executable.

Note: As the raspberry pi runs a linux based system it is reccomended that you make changes to the Game System on a linux system and therefore no instructions are provided for a Windows setup.

It is possible to set up the raspberry pi to run MarpleTilt on boot up. Instructions on how to achieve this can be found at the following website:
https://www.dexterindustries.com/howto/run-a-program-on-your-raspberry-pi-at-startup/#:~:text=The%20first%20method%20to%20run,local%20file.
