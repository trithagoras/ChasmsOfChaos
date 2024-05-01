cmake_minimum_required(VERSION 3.10)
project(chasms VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20")

# Find SFML components
find_package(SFML 2.6 COMPONENTS graphics audio REQUIRED)

# libtcod (TODO: make this more portable; use vcpkg + find_package)
include_directories("/opt/homebrew/Cellar/libtcod/1.24.0/include")
link_directories("/opt/homebrew/Cellar/libtcod/1.24.0/lib")

# json
find_package(nlohmann_json 3.11.3 REQUIRED)

add_executable(chasms game.cpp canyon-6x5.h component.h contentprovider.h contentprovider.cpp floor.cpp floor.h gamecolors.h gameobject.cpp gameobject.h gameobjectfactory.h gameobjectfactory.cpp item.h itemc.h itemc.cpp jail-10x10.h ladderc.h ladderc.cpp moat-12x16.h playerc.cpp playerc.h rooms.h spritefactory.cpp spritefactory.h treasure-room-12x6.h utils.h world.cpp world.h)

target_link_libraries(chasms PRIVATE sfml-graphics sfml-audio)
target_link_libraries(chasms PRIVATE tcod)
target_link_libraries(chasms PRIVATE nlohmann_json::nlohmann_json)
