cmake_minimum_required(VERSION 2.8)
project(MatchMaster)

set(SOURCE_FILES main.cpp
        MatchMaster.cpp
)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})


if(WIN32)
    target_link_libraries(${PROJECT_NAME} mingw32 STRData ${SDL2main} ${SDL2} ${SDL2_image} ${SDL2_ttf} ${SDL2_net} ${SDL2_gfx} ${StiGame})
elseif(UNIX)
    target_link_libraries(${PROJECT_NAME} STRData ${SDL2main} ${SDL2} ${SDL2_image} ${SDL2_ttf} ${SDL2_net} ${SDL2_gfx} ${StiGame})
endif(WIN32)

install(TARGETS ${PROJECT_NAME} DESTINATION ${INSTALL_DIR})
