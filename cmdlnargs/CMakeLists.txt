cmake_minimum_required(VERSION 3.10)
project(cmdlnargs)

include_directories(${CMAKE_CURRENT_BINARY_DIR})

set(SOURCE_CMDLNARGS
    cargparser.cpp)
set(HEADERS_CMDLNARGS
    cargparser.h)

add_library(cmdlnargs STATIC ${SOURCE_CMDLNARGS} ${HEADERS_CMDLNARGS})
