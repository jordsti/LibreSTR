cmake_minimum_required(VERSION 2.8)
project(STRData)

set(SOURCE_FILES MapData.cpp
            Directory.cpp
            Entry.cpp
            File.cpp
            FileSystem.cpp)

add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES})
