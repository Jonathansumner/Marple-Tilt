cmake_minimum_required(VERSION 3.18.4)

project(MarpleTilt)

execute_process(COMMAND GraphicsMagick++-config --cppflags --cxxflags OUTPUT_VARIABLE MAGICK_CXX_FLAGS OUTPUT_STRIP_TRAILING_WHITESPACE)

string(REPLACE "\n" " " MAGICK_CXX_FLAGS_STRIPPED ${MAGICK_CXX_FLAGS})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${MAGICK_CXX_FLAGS_STRIPPED}")

execute_process(COMMAND GraphicsMagick++-config --ldflags --libs OUTPUT_VARIABLE MAGICK_LDF_FLAGS OUTPUT_STRIP_TRAILING_WHITESPACE)

string(REPLACE "\n" " " MAGICK_LDF_FLAGS_STRIPPED ${MAGICK_LDF_FLAGS})

add_executable(${PROJECT_NAME} 
    source/main.cpp
    source/object.cpp source/game-objects.cpp
    source/collision-box.cpp source/collision-boxes.cpp
    source/button.cpp source/buttons.cpp
    source/loading-bar.cpp source/textbox.cpp
    source/render.cpp source/images.cpp
    source/menu-pages.cpp
    source/dynamics.cpp 
    source/game-states.cpp source/menu-states.cpp 
    source/marple-tilt-machine.cpp source/base-state.cpp
    source/map-loader.cpp)

add_subdirectory(external/mpu6050-api)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

add_library(matrixAPI STATIC IMPORTED)
set_target_properties(matrixAPI PROPERTIES
    IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/external/matrix-api/lib/librgbmatrix.a
    INTERFACE_INCLUDE_DIRECTORIES ${CMAKE_SOURCE_DIR}/external/matrix-api/include
    )

include_directories(
    ${CMAKE_SOURCE_DIR}/external/matrix-api/include
    ${CMAKE_SOURCE_DIR}/external/mpu6050-api/src
    ${CMAKE_SOURCE_DIR}/include
    )

target_link_directories(${PROJECT_NAME}
    PRIVATE ${CMAKE_SOURCE_DIR}/external/mpu6050-api/build/
)

target_link_libraries(${PROJECT_NAME}
    matrixAPI
    "-lpigpio"
    Threads::Threads
    ${MAGICK_LDF_FLAGS_STRIPPED}
    "-lrt"
    mpu6050
    )

install(TARGETS ${PROJECT_NAME} DESTINATION ${CMAKE_INSTALL_PREFIX})