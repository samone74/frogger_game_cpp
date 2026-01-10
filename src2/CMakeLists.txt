add_library(frogger_core2
            game.cpp
            game.h
            objects/object_base.h
        objects/frog.cpp
        objects/frog.h
        objects/lanes.cpp
        objects/lanes.h
        objects/car.cpp
        objects/car.h
        objects/lives.cpp
        objects/lives.h
        objects/night.cpp
        objects/night.h

)

target_include_directories(frogger_core2 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(frogger_core2 PRIVATE ${SDL3_INCLUDE_DIR})
target_include_directories(frogger_core2 PRIVATE ${SDL3_TFF_INCLUDE_DIR})