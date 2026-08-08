cmake_minimum_required(VERSION 4.0)
project(
    Astroids
    VERSION 1.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 23)

find_package(SDL3 REQUIRED)
find_package(SDL3_image REQUIRED)

find_package(PkgConfig REQUIRED)
pkg_check_modules(SDL3_GFX REQUIRED IMPORTED_TARGET sdl3-gfx)

add_executable(Astroids
    sources/main.cpp
    includes/Sprite.hpp
    includes/Types.hpp
    includes/Player.hpp
    sources/Player.cpp
    includes/Bullet.hpp
    sources/Bullet.cpp
)

target_include_directories(Astroids PUBLIC
    ${CMAKE_SOURCE_DIR}/includes
)

target_link_libraries(Astroids PUBLIC
    SDL3::SDL3
    SDL3_image::SDL3_image
    PkgConfig::SDL3_GFX
)

set(ASSET_FOLDER_NAME "assets")

add_custom_command(TARGET Astroids POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_CURRENT_SOURCE_DIR}/${ASSET_FOLDER_NAME}"
        "$<TARGET_FILE_DIR:Astroids>/${ASSET_FOLDER_NAME}"
    COMMENT "Copying game assets to the target output directory..."
)
