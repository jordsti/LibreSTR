cmake_minimum_required(VERSION 2.8)
project(LibreSTR)

set(SOURCE_FILES main.cpp
    AssetManager.cpp
    GameMap.cpp
    GameOverlay.cpp
    GameState.cpp
    #HydrocarbonGaz.cpp will be remove too
    IResource.cpp
    LibreSTRStyle.cpp
    MainMenu.cpp
    MapGenerator.cpp
    PlayerMap.cpp
    Tile.cpp
    TopHud.cpp
    #Titanium.cpp this file will be removed
    VFResource.cpp
)

configure_file(VersionConfig.h.in ${CMAKE_BINARY_DIR}/generated/VersionConfig.h)
include_directories(${CMAKE_BINARY_DIR}/generated/)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} mingw32 ${SDL2main} ${SDL2} ${SDL2_image} ${SDL2_ttf} ${SDL2_net} ${SDL2_gfx} ${StiGame})

install(TARGETS ${PROJECT_NAME} DESTINATION ${INSTALL_DIR})
