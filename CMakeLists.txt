cmake_minimum_required(VERSION 2.8)
project(LibreSTRRoot)

set(LIBRESTR_MAJOR 0)
set(LIBRESTR_MINOR 0)
set(LIBRESTR_RELEASE 1)

if(NOT LIBRESTR_BUILD)
    set(LIBRESTR_BUILD 0)
endif(NOT LIBRESTR_BUILD)

set(LIBRESTR_NAME "whatisrts")

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -DDEBUG")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O2 -DRELEASE")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall")

if(NOT STIGAME_PATH)
        set(STIGAME_PATH "${PROJECT_SOURCE_DIR}/../stigame/build/${CMAKE_BUILD_TYPE}/*/")
else(NOT STIGAME_PATH)
        set(STIGAME_PATH "${PROJECT_SOURCE_DIR}/${STIGAME_PATH}")
endif(NOT STIGAME_PATH)


if(NOT SDL2_LIBS)
	if(WIN32)
		set(SDL2_LIBS "${PROJECT_SOURCE_DIR}/lib/")
	elseif(UNIX)
		set(SDL2_LIBS "/usr/lib/")
	endif(WIN32)
endif(NOT SDL2_LIBS)

if(NOT SDL2_INCLUDE)
	if(WIN32)
		set(SDL2_INCLUDE "include/SDL2")
	elseif(UNIX)
		set(SDL2_INCLUDE "/usr/include/SDL2")
	endif(WIN32)
endif(NOT SDL2_INCLUDE)

include_directories(${SDL2_INCLUDE})
include_directories(STRData)

if(TRAVIS_BUILD)
	include_directories(stigame/StiGame/)
    #need sdl2_gfx header
    include_directories("${PROJECT_SOURCE_DIR}/include/SDL2")
else(TRAVIS_BUILD)
	include_directories(../stigame/StiGame)
endif(TRAVIS_BUILD)

if(NOT STIGAME_INCLUDE)
	include_directories(stigame/StiGame/)
else(NOT STIGAME_INCLUDE)
	include_directories(${STIGAME_INCLUDE})
endif(NOT STIGAME_INCLUDE)


find_library(SDL2 NAMES "SDL2" PATHS ${SDL2_LIBS})
find_library(SDL2_image NAMES "SDL2_image" PATHS ${SDL2_LIBS})
find_library(SDL2_gfx NAMES "SDL2_gfx" PATHS ${SDL2_LIBS})
find_library(SDL2_ttf NAMES "SDL2_ttf" PATHS ${SDL2_LIBS})
find_library(SDL2_net NAMES "SDL2_net" PATHS ${SDL2_LIBS})
find_library(SDL2main NAMES "SDL2main" PATHS ${SDL2_LIBS})
find_library(StiGame NAMES "StiGame" PATHS ${STIGAME_PATH} FORCE)

if(NOT StiGame)
        find_library(StiGame NAMES "StiGame" PATHS ${PROJECT_SOURCE_DIR}/stigame/build/${CMAKE_BUILD_TYPE}/*/ FORCE)
endif(NOT StiGame)

if(CMAKE_BUILD_TYPE STREQUAL "Release")
    if(LIBRESTR_NAME STREQUAL "")
        set(INSTALL_DIR ${PROJECT_SOURCE_DIR}/build/${CMAKE_BUILD_TYPE}/${LIBRESTR_MAJOR}.${LIBRESTR_MINOR}.${LIBRESTR_RELEASE}.${LIBRESTR_BUILD})
    else(LIBRESTR_NAME STREQUAL "")
        set(INSTALL_DIR ${PROJECT_SOURCE_DIR}/build/${CMAKE_BUILD_TYPE}/${LIBRESTR_MAJOR}.${LIBRESTR_MINOR}.${LIBRESTR_RELEASE}.${LIBRESTR_BUILD}-${LIBRESTR_NAME})
    endif(LIBRESTR_NAME STREQUAL "")
else(CMAKE_BUILD_TYPE STREQUAL "Release")
    set(INSTALL_DIR ${PROJECT_SOURCE_DIR}/build/${CMAKE_BUILD_TYPE}/last)
endif(CMAKE_BUILD_TYPE STREQUAL "Release")

add_subdirectory(STRData)
add_subdirectory(LibreSTR)


if(WIN32)
    get_filename_component(MINGW32_ROOT ${CMAKE_CXX_COMPILER} DIRECTORY)
    install(DIRECTORY bin/ DESTINATION ${INSTALL_DIR} FILES_MATCHING PATTERN "*.dll")
    install(FILES "${MINGW32_ROOT}/libstdc++-6.dll" DESTINATION ${INSTALL_DIR})
    install(FILES ${StiGame} DESTINATION ${INSTALL_DIR})
endif(WIN32)

install(DIRECTORY assets DESTINATION ${INSTALL_DIR} CONFIGURATIONS Release FILES_MATCHING PATTERN "*.*")
