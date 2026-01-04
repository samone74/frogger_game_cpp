add_library(frogger_core
        Game.cpp
        Frog.cpp
        Lane.cpp
        Car.cpp
)

target_include_directories(frogger_core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
