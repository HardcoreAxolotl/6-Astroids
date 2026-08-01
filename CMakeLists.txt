cmake_minimum_required(VERSION 4.0)
project(
    Astroids
    VERSION 1.0
    LANGUAGES CXX
)

find_package(SDL3 REQUIRED)

add_executable(Astroids
    sources/main.cpp
)

target_link_libraries(Astroids PUBLIC
    SDL3::SDL3
)