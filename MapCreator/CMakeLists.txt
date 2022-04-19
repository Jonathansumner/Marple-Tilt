cmake_minimum_required(VERSION 3.18.4)
project(MapCreator LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR on)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 REQUIRED COMPONENTS
        Core
        Gui
        Widgets)

add_executable(${PROJECT_NAME} 
        main.cpp 
        window.cpp Paint.cpp
        ColourPick.cpp)

target_link_libraries(${PROJECT_NAME}
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        )

if (WIN32)
    set(CMAKE_WIN32_EXECUTABLE ON)
endif()