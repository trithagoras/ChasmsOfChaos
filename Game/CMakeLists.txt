cmake_minimum_required (VERSION 3.21)

# Set the default toolchain to use a Vcpkg submodule.
if(NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(CMAKE_TOOLCHAIN_FILE
        "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake"
        CACHE STRING "Vcpkg toolchain file")
endif()

project(chasms VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Find SFML components
find_package(SFML 2.6 COMPONENTS graphics CONFIG REQUIRED)

find_package(nlohmann_json CONFIG REQUIRED)
find_package(libtcod CONFIG REQUIRED)

add_executable(chasms game.cpp canyon-6x5.h component.h contentprovider.h contentprovider.cpp floor.cpp floor.h gamecolors.h gameobject.cpp gameobject.h gameobjectfactory.h gameobjectfactory.cpp item.h itemc.h jail-10x10.h ladderc.h moat-12x16.h playerc.cpp playerc.h rooms.h spritefactory.cpp spritefactory.h treasure-room-12x6.h utils.h world.cpp world.h ui.h ui.cpp)

target_link_libraries(chasms PRIVATE sfml-graphics)
target_link_libraries(chasms PRIVATE nlohmann_json::nlohmann_json libtcod::libtcod)
