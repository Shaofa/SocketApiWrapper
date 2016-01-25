cmake_minimum_required(VERSION 2.8)

set(EXECUTABLE_OUTPUT_PATH ./bin)
set(CMAKE_C_COMPLIER "gcc")
set(CMAKE_C_FLAGS_DEBUG "-g")
set(CMAKE_C_FLAGS "-g")

aux_source_directory(../common SRC)
include_directories(../common)

add_executable(client ./src/client.c ${SRC})
add_executable(server ./src/server.c ${SRC})
