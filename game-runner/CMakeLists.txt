cmake_minimum_required(VERSION 3.18.4)

project(MarpleTilt)

execute_process(COMMAND GraphicsMagick++-config --cppflags --cxxflags --ldflags --libs OUTPUT_VARIABLE MAGICK_FLAGS OUTPUT_STRIP_TRAILING_WHITESPACE)

string(STRIP ${MAGICK_FLAGS} MAGICK_FLAGS_STRIPPED)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -I/usr/include/GraphicsMagick -g -O2 -ffile-prefix-map=/build/graphicsmagick-t7apbd/graphicsmagick-1.4+really1.3.36+hg16481=. -fstack-protector-strong -Wformat -Werror=format-security -pthread -L/usr/lib -Wl,-z,relro -Wl,-z,now -L/usr/lib/X11 -lGraphicsMagick++ -lGraphicsMagick -ljbig -lwebp -lwebpmux -llcms2 -ltiff -lfreetype -ljpeg -lpng16 -lwmflite -lXext -lSM -lICE -lX11 -llzma -lbz2 -lxml2 -lz -lzstd -lm -lpthread -lgomp -pthread")

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
include_directories(${CMAKE_SYSROOT}/usr/include/GraphicsMagick)

target_link_libraries(${PROJECT_NAME} 
    mpu6050API
    matrixAPI
    Threads::Threads
    )

install(TARGETS ${PROJECT_NAME} DESTINATION ${CMAKE_INSTALL_PREFIX})