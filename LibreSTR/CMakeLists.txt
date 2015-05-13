cmake_minimum_required(VERSION 2.8)
project(LibreSTR)

set(SOURCE_FILES main.cpp
    AssetManager.cpp
    GameObject.cpp
    GameObjectListener.cpp
    GameState.cpp
    GameLoadingState.cpp
    GameLoader.cpp
    MainMenu.cpp
    NewGameMenu.cpp
    Player.cpp
    MPlayer.cpp
    LoadingState.cpp
    LoadableObject.cpp
    MatchMasterClient.cpp
    MatchBrowser.cpp

    server/GameServer.cpp
    server/PlayerConnection.cpp

    client/GameClient.cpp

    ai/CompLeafAction.cpp
    ai/CompLeafCondition.cpp
    ai/MLeaf.cpp
    ai/Leaf.cpp
    ai/LeafCondition.cpp
    ai/LeafAction.cpp

    actions/ToggleConsole.cpp
    actions/ToggleMiniMapAction.cpp
    actions/ToggleShowFPSAction.cpp
    actions/ViewMoveAction.cpp
    actions/PauseGameAction.cpp


    gui/Console.cpp
    gui/ErrorLabel.cpp
    gui/LibreSTRStyle.cpp
    gui/ILogStream.cpp
    gui/MiniMap.cpp
    gui/TopHud.cpp
    gui/GameOverlay.cpp
    gui/RadialMenu.cpp
    gui/RadialItem.cpp
    gui/UnitInfoPanel.cpp
    gui/MultiSelectionPanel.cpp

    units/Building.cpp
    units/BuildingIdentity.cpp
    units/BuildingSprite.cpp
    units/BuildTask.cpp
    units/MBuilding.cpp
    units/GroundUnitIdentity.cpp
    units/GroundUnit.cpp
    units/GroundUnitSpriteManager.cpp
    units/MGroundUnit.cpp
    units/Unit.cpp
    units/UnitSprite.cpp
    units/JobEmitter.cpp
    units/Job.cpp
    units/CreateUnitJob.cpp
    units/CreateUnitEmitter.cpp
    units/Task.cpp
    units/MoveTask.cpp
    units/HarvestTask.cpp
    units/AttackGroundUnitTask.cpp
    units/AttackBuildingTask.cpp
    units/UnitPath.cpp
    units/UnitPathNode.cpp
    units/UnitPathThread.cpp

    maps/GameMap.cpp
    maps/GameMapEvent.cpp
    maps/GameMapEventListener.cpp
    maps/GameMapEventThrower.cpp
    maps/IResource.cpp
    maps/ITileMap.cpp
    maps/Resource.cpp
    maps/MapGenerator.cpp
    maps/PlayerMap.cpp
    maps/Tile.cpp
    maps/ResourceIdentity.cpp
    maps/BitMap.cpp

    LibreSTRVersion.cpp
)

configure_file(LibreSTRVersion.cpp.in ${PROJECT_SOURCE_DIR}/LibreSTRVersion.cpp)
add_executable(${PROJECT_NAME} ${SOURCE_FILES})

include_directories(".")
include_directories(actions)
include_directories(gui)
include_directories(units)
include_directories(maps)
include_directories(server)
include_directories(client)


if(WIN32)
    target_link_libraries(${PROJECT_NAME} mingw32 STRData ${SDL2main} ${SDL2} ${SDL2_image} ${SDL2_ttf} ${SDL2_net} ${SDL2_gfx} ${StiGame})
elseif(UNIX)
    target_link_libraries(${PROJECT_NAME} STRData ${SDL2main} ${SDL2} ${SDL2_image} ${SDL2_ttf} ${SDL2_net} ${SDL2_gfx} ${StiGame})
endif(WIN32)

install(TARGETS ${PROJECT_NAME} DESTINATION ${INSTALL_DIR})
