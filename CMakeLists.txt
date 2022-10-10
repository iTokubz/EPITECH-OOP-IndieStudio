cmake_minimum_required(VERSION 3.17)
project(bomberman)
include (cmake/Findraylib.cmake)

set(CMAKE CXX STANDARD 20)
set(CMAKE_EXE_LINKER_FLAGS "-W -Wall -Wextra -Werror -g ")
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wall -g")

set(SRC
    Core/main.cpp
    AssetsManager/AssetsLoader.cpp
    Core/Core.cpp
    Core/Menu/Menu.cpp
    ECS/ECS.cpp
    Core/IA/ia.cpp
    GameEngine/Engine.cpp
    )

add_executable(bomberman ${SRC})
target_link_libraries(bomberman raylib -lstdc++fs)
set_target_properties(bomberman PROPERTIES RUNTIME_OUTPUT_DIRECTORY "../")