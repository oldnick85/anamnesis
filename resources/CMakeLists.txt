cmake_minimum_required(VERSION 3.13)
project(resources)
message("\nBEGIN " ${PROJECT_NAME})

include_directories(${CMAKE_CURRENT_BINARY_DIR})

set(HEADERS_RESOURCES
    ctextresources.h
    textresult.h
    )
set(SOURCE_RESOURCES
    ctextresources.cpp
    )

add_library(resources ${SOURCE_RESOURCES} ${HEADERS_RESOURCES})

message("END " ${PROJECT_NAME} "\n")
