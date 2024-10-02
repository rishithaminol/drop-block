cmake_minimum_required(VERSION 3.27)

project(drop-block VERSION 0.1.0)
set(PROJECT_VERSION_MAJOR 0)
set(PROJECT_VERSION_MINOR 1)
set(PROJECT_VERSION_PATCH 0)

include_directories(${CMAKE_BINARY_DIR})
add_compile_options(-Wall -Wextra -Wpedantic)

set(BUILD_SHARED_LIBS OFF)
set(CMAKE_BUILD_TYPE Debug)

set(SOURCES
    src/drop-block.c
    src/quad.c
    src/shaders.c
    src/utils.c
)

# -------------------------- libsdl2 build process ---------------------------
set(SDL2_SOURCE_DIR ${CMAKE_SOURCE_DIR}/SDL2)
set(SDL2_BIN_DIR ${SDL2_SOURCE_DIR}/build)

add_custom_command(
    OUTPUT ${SDL2_BIN_DIR}/libSDL2.a
    COMMAND ${CMAKE_COMMAND} -E make_directory ${SDL2_BIN_DIR}
    COMMAND ${CMAKE_COMMAND} -E chdir ${SDL2_BIN_DIR} ${CMAKE_COMMAND} -DSDL_WAYLAND_LIBDECOR=ON ..
    COMMAND ${CMAKE_COMMAND} -E chdir ${SDL2_BIN_DIR} make
    WORKING_DIRECTORY ${SDL2_SOURCE_DIR}
    COMMENT "Building SDL2 library"
)

add_custom_target(libsdl2-build DEPENDS ${SDL2_BIN_DIR}/libSDL2.a)
# -------------------------- libsdl2 build process ---------------------------

add_executable(${PROJECT_NAME} ${SOURCES})
add_dependencies(${PROJECT_NAME} libsdl2-build)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${SDL2_SOURCE_DIR}/include
    ${SDL2_BIN_DIR}/include
)

target_link_libraries(${PROJECT_NAME} ${SDL2_BIN_DIR}/libSDL2.a
    pthread
    m
    GLEW
    GL
)

set(BUILD_SHARED_LIBS OFF)
