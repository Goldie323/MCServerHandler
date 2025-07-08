cmake_minimum_required(VERSION 3.10)
project(MCServerHandler C)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

include_directories(include src/cjson)

add_library(MCServerHandler SHARED
    src/MCServerHandler.c
    src/cjson/cJSON.c
)

target_include_directories(MCServerHandler PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)
