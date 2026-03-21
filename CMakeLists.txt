cmake_minimum_required(VERSION 3.23)
project(RaycasterWolf)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})
include_directories(${SDL2_IMAGE_INCLUDE_DIRS})

add_executable(RaycasterWolf
    src/main.cpp
    src/Map.cpp
    src/Sprite.cpp
    src/Player.cpp
    src/EnemyAI.cpp
    src/Renderer.cpp
    src/Game.cpp
)

target_link_libraries(RaycasterWolf ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES})

file(COPY src/assets DESTINATION ${CMAKE_BINARY_DIR})
