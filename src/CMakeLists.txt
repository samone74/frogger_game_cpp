add_library(frogger_core
        objects/game_objects/object_base.h
        objects/game_objects/frog.cpp
        objects/game_objects/frog.h
        objects/game_objects/lanes.cpp
        objects/game_objects/lanes.h
        objects/game_objects/car.cpp
        objects/game_objects/car.h
        objects/game_objects/lives.cpp
        objects/game_objects/lives.h
        objects/game_objects/count_down_timer.cpp
        objects/game_objects/count_down_timer.h
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
        objects/draw_objects/draw_object_base.h
        objects/draw_objects/draw_object_text.cpp
        objects/draw_objects/draw_object_text.h
        objects/draw_objects/draw_object_sprite.cpp
        objects/draw_objects/draw_object_sprite.h
        objects/draw_objects/draw_object_rect.cpp
        objects/draw_objects/draw_object_rect.h
        objects/color.h
        objects/rectangle.h

)

target_include_directories(frogger_core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(frogger_core PRIVATE ${SDL3_INCLUDE_DIR})
target_include_directories(frogger_core PRIVATE ${SDL3_TFF_INCLUDE_DIR})
target_include_directories(frogger_core PRIVATE ${SDL3_IMAGE_INCLUDE_DIR})

