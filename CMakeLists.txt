cmake_minimum_required(VERSION 3.7)
project(snake)

set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR}/dist)

add_compile_definitions(
    RESOURCES_PATH="${CMAKE_INSTALL_PREFIX}/share")

link_libraries(
    SDL2
    SDL2_ttf
)

add_executable(
    snake
    src/Logger.cpp
    src/Game.cpp
    src/Text.cpp
    src/Window.cpp
    src/main.cpp
)

install(DIRECTORY resources TYPE DATA)
install(TARGETS snake)

