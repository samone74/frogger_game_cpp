cmake_minimum_required(VERSION 3.30)
project(frogger)

set(CMAKE_CXX_STANDARD 23)

project(Frogger LANGUAGES CXX)
set(SDL3_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/lib/SDL3-3.2.28/x86_64-w64-mingw32/include")
set(SDL3_LIBRARY    "${CMAKE_SOURCE_DIR}/lib/SDL3-3.2.28/x86_64-w64-mingw32/lib/libSDL3.dll.a") # or SDL3.a for MinGW


add_subdirectory(src)
add_subdirectory(src2)
add_subdirectory(desktop)
