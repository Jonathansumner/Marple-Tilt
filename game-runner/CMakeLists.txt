cmake_minimum_required(VERSION 3.18.4)

project(MarpleTilt)

add_executable(${PROJECT_NAME} main.cpp)

include_directories(${CMAKE_SOURCE_DIR}/external/matrix-api/include)
include_directories(${CMAKE_SOURCE_DIR}/external/mpu6050-api)

target_link_libraries(${PROJECT_NAME} 
    ${CMAKE_SOURCE_DIR}/external/mpu6050-api/libMPU6050.so 
    ${CMAKE_SOURCE_DIR}/external/matrix-api/lib/librgbmatrix.a
    )