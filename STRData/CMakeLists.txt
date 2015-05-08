cmake_minimum_required(VERSION 2.8)
project(STRData)

set(SOURCE_FILES MapData.cpp
    Match.cpp)

add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES})
