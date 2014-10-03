cmake_minimum_required(VERSION 2.8)
project(LibreSTRRoot)

set(LIBRESTR_MAJOR 0)
set(LIBRESTR_MINOR 0)
set(LIBRESTR_RELEASE 0)
set(LIBRESTR_BUILD 1)
set(LIBRESTR_NAME "whatisrts?")

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -DDEBUG")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O2 -DRELEASE")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall")

include_directories(include/SDL2)
include_directories(../stigame/StiGame)

if(WIN32)
find_library(SDL2 NAMES "SDL2" PATHS ${PROJECT_SOURCE_DIR}/lib/)
find_library(SDL2_image NAMES "SDL2_image" PATHS ${PROJECT_SOURCE_DIR}/lib/)
find_library(SDL2_gfx NAMES "SDL2_gfx" PATHS ${PROJECT_SOURCE_DIR}/lib/)
find_library(SDL2_ttf NAMES "SDL2_ttf" PATHS ${PROJECT_SOURCE_DIR}/lib/)
find_library(SDL2_net NAMES "SDL2_net" PATHS ${PROJECT_SOURCE_DIR}/lib/)
find_library(SDL2main NAMES "SDL2main" PATHS ${PROJECT_SOURCE_DIR}/lib/)
find_library(StiGame NAMES "StiGame" PATHS ${PROJECT_SOURCE_DIR}/../StiGame/build/*/${CMAKE_BUILD_TYPE} FORCE)
endif(WIN32)

if(CMAKE_BUILD_TYPE EQUAL "Release")
    set(INSTALL_DIR ${PROJECT_SOURCE_DIR}/build/${LIBRESTR_MAJOR}.${LIBRESTR_MINOR}.${LIBRESTR_RELEASE}.${LIBRESTR_BUILD}/${CMAKE_BUILD_TYPE})
else(CMAKE_BUILD_TYPE EQUAL "Release")
    set(INSTALL_DIR ${PROJECT_SOURCE_DIR}/build/last/${CMAKE_BUILD_TYPE})
endif(CMAKE_BUILD_TYPE EQUAL "Release")

add_subdirectory(LibreSTR)

#get_filename_component(StiGame_dll ${StiGame} DIRECTORY)

if(WIN32)
    get_filename_component(MINGW32_ROOT ${CMAKE_CXX_COMPILER} DIRECTORY)
    install(DIRECTORY bin/ DESTINATION ${INSTALL_DIR} FILES_MATCHING PATTERN "*.dll")
    install(FILES "${MINGW32_ROOT}/libstdc++-6.dll" DESTINATION ${INSTALL_DIR})
endif(WIN32)
message("Using StiGame Lib in : ${StiGame}")
install(FILES ${StiGame} DESTINATION ${INSTALL_DIR})
install(DIRECTORY assets DESTINATION ${INSTALL_DIR} CONFIGURATIONS Release FILES_MATCHING PATTERN "*.*")
