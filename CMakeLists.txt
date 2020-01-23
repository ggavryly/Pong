cmake_minimum_required(VERSION 3.7)
project(Pong)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake_modules/")
set(CMAKE_FRAMEWORK_PATH "./lib/")
set(CMAKE_CXX_STANDARD 11)
set(SOURCE src/)
set(INCLUDE includes/)
set(SDL2_PATH ./lib/)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})
find_package(SDL2_image REQUIRED)
include_directories(${SDL2_IMAGE_INCLUDE_DIRS})
find_package(SDL2_ttf REQUIRED)
include_directories(${SDL2_TTF_INCLUDE_DIRS})

include_directories(
        ${SOURCE}
        ${INCLUDE})

link_directories(
        ${SOURCE}
        ${INCLUDE})

file(GLOB all
        "${INCLUDE}*.hpp"
        "${SOURCE}*.cpp")

add_executable(${PROJECT_NAME} ${all} src/Player.cpp includes/Player.hpp src/Ball.cpp includes/Ball.hpp includes/GameEntity.hpp src/Game.cpp includes/Game.hpp)

target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} ${SDL2_TTF_LIBRARIES})
