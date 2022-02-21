cmake_minimum_required(VERSION 3.18.4)

project(MarpleTilt)
add_executable(${PROJECT_NAME} main.cpp graphics/gfx.cpp graphics/gfx.h)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

add_library(matrixAPI STATIC IMPORTED)
set_target_properties(matrixAPI PROPERTIES IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/external/matrix-api/lib/librgbmatrix.a)
set_target_properties(matrixAPI PROPERTIES INTERFACE_INCLUDE_DIRECTORIES ${CMAKE_SOURCE_DIR}/external/matrix-api/include)

add_library(mpu6050API SHARED IMPORTED GLOBAL)
set_target_properties(mpu6050API PROPERTIES IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/external/mpu6050-api/libMPU6050.so)
set_target_properties(mpu6050API PROPERTIES INTERFACE_INCLUDE_DIRECTORIES ${CMAKE_SOURCE_DIR}/external/mpu6050-api)
set_target_properties(mpu6050API PROPERTIES IMPORTED_SONAME "libMPU6050.so")


include_directories(${CMAKE_SOURCE_DIR}/external/matrix-api/include)
include_directories(${CMAKE_SOURCE_DIR}/external/mpu6050-api)

target_link_libraries(${PROJECT_NAME} 
    mpu6050API
    matrixAPI
    Threads::Threads
    )

install(TARGETS ${PROJECT_NAME} DESTINATION ${CMAKE_INSTALL_PREFIX})