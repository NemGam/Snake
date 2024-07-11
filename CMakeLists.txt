cmake_minimum_required(VERSION 3.13)
project(snake)

set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR}/dist)

add_compile_definitions(
    RESOURCES_PATH="${CMAKE_INSTALL_PREFIX}/share")


add_executable(
    ${PROJECT_NAME}
    src/logger.cpp
    src/game.cpp
    src/text.cpp
    src/window.cpp
    src/main.cpp
    src/unique_ptrs_destructors.cpp
)

target_compile_options(${PROJECT_NAME} PRIVATE -Wall -pedantic)

target_link_libraries(
    ${PROJECT_NAME}
    SDL2
    SDL2_ttf
)

install(DIRECTORY resources TYPE DATA)
install(TARGETS ${PROJECT_NAME})

