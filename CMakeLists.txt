cmake_minimum_required(VERSION 3.14)

project(
    coro_game_map
    VERSION 0.1.0
    DESCRIPTION "Game map generation with coro"
    HOMEPAGE_URL "https://example.com/"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_C_STANDARD 20)
set(CMAKE_CXX_FLAGS "-ltbb")


# --- Resource path ----
add_compile_definitions(_RESOURCE_PATH=\"${CMAKE_SOURCE_DIR}/resource/\")


# ---- Declare executable ----
add_executable(coro_game_map_exe 
    source/CellGenerator.cpp
    source/main.cpp 
    source/Cell.cpp 
    source/Player.cpp
    source/Game.cpp
)

# ---- Coro package ----
find_package(cppcoro REQUIRED)

if(cppcoro_FOUND)
    target_link_libraries(coro_game_map_exe PRIVATE cppcoro::cppcoro)
endif()

# ---- SFML ----
find_package(SFML REQUIRED system window graphics network audio)

if(SFML_FOUND)
    target_include_directories(coro_game_map_exe PRIVATE ${SFML_INCLUDE_DIRECTORIES})
    message("sfml: " ${SFML_LIBRARIES})
    target_link_libraries(coro_game_map_exe PRIVATE sfml-system sfml-window sfml-graphics)
endif()
