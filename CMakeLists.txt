cmake_minimum_required(VERSION 3.0)
project(PacMan C)

set(CMAKE_C_STANDARD 99)

# Setting parameters for raylib
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
set(BUILD_GAMES    OFF CACHE BOOL "" FORCE) # or games

add_subdirectory(libs/raylib)

set(SRC_FILES src/main.c src/globals.c)
set(SRC_OBJ_FILES src/objects/player.c src/objects/enemy.c src/objects/edible.c)
set(SRC_MGT_FILES src/management/level-manager.c src/management/sprite-manager.c)

add_executable(PacMan ${SRC_FILES} ${SRC_OBJ_FILES} ${SRC_MGT_FILES})
target_link_libraries(PacMan PRIVATE raylib)