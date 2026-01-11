cmake_minimum_required(VERSION 3.30)
project(frogger)

set(CMAKE_CXX_STANDARD 23)

project(Frogger LANGUAGES CXX)
set(SDL3_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/lib/SDL3-3.2.28/x86_64-w64-mingw32/include")
set(SDL3_TFF_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/lib/SDL3_ttf-3.2.2/x86_64-w64-mingw32/include")
set(SDL3_LIBRARY    "${CMAKE_SOURCE_DIR}/lib/SDL3-3.2.28/x86_64-w64-mingw32/lib/libSDL3.dll.a") # or SDL3.a for MinGW
set(SDL3_TFF_LIBRARY    "${CMAKE_SOURCE_DIR}/lib/SDL3_ttf-3.2.2/x86_64-w64-mingw32/lib/libSDL3_ttf.dll.a" )


add_subdirectory(src)
add_subdirectory(desktop)

