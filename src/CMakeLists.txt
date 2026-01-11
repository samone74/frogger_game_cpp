add_library(frogger_core
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
        objects/text_object.cpp
        objects/text_object.h
        objects/count_down_timer.cpp
        objects/count_down_timer.h

)

target_include_directories(frogger_core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(frogger_core PRIVATE ${SDL3_INCLUDE_DIR})
target_include_directories(frogger_core PRIVATE ${SDL3_TFF_INCLUDE_DIR})