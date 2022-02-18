cmake_minimum_required(VERSION 3.20.0)

project(MarpleTilt)

add_executable(${PROJECT_NAME} main.cpp)

include_directories(${CMAKE_SOURCE_DIR}/external/matrix-api/include)
include_directories(${CMAKE_SOURCE_DIR}/external/mpu6050-api)