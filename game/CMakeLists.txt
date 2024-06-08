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

# copy content directory
set(CONTENT_SOURCE_DIR "${CMAKE_SOURCE_DIR}/../content")
set(CONTENT_DEST_DIR "${CMAKE_BINARY_DIR}/content")

add_custom_target(copy_content ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CONTENT_SOURCE_DIR} ${CONTENT_DEST_DIR}
    COMMENT "Copying content directory to build directory"
)

# Find SFML components
find_package(SFML 2.5 COMPONENTS graphics CONFIG REQUIRED)

find_package(nlohmann_json CONFIG REQUIRED)
find_package(libtcod CONFIG REQUIRED)

include_directories(include)

add_executable(${PROJECT_NAME} src/game.cpp src/contentprovider.cpp src/floor.cpp src/gameobject.cpp src/gameobjectfactory.cpp src/playerc.cpp src/spritefactory.cpp src/world.cpp src/ui.cpp "include/soundplayer.h" "src/soundplayer.cpp")

target_link_libraries(${PROJECT_NAME} PRIVATE sfml-graphics sfml-audio)
target_link_libraries(${PROJECT_NAME} PRIVATE nlohmann_json::nlohmann_json libtcod::libtcod)

add_dependencies(${PROJECT_NAME} copy_content)
