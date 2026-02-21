add_library(frogger_core
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
        game_states/game_state.h
        game.cpp
        game.h
        game_states/game_state_manager.cpp
        game_states/game_state_manager.h
        objects/sdl_context.h
        objects/sdl_context.cpp
        game_states/transition.h
        game_states/main_game_state.cpp
        game_states/main_game_state.h
        game_states/start_screen.cpp
        game_states/start_screen.h
        game_states/lose_screen.cpp
        game_states/lose_screen.h
        game_states/win_screen.cpp
        game_states/win_screen.h
        objects/sprite_object.cpp
        objects/sprite_object.h
        objects/draw_object_base.h

)

target_include_directories(frogger_core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(frogger_core PRIVATE ${SDL3_INCLUDE_DIR})
target_include_directories(frogger_core PRIVATE ${SDL3_TFF_INCLUDE_DIR})
target_include_directories(frogger_core PRIVATE ${SDL3_IMAGE_INCLUDE_DIR})

