#include "game.h"
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

extern "C" int SDL_main(int argc, char *argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_EVENTS) < 0) {
        SDL_Log("SDL_Init failed: %s", SDL_GetError());
        return 1;
    }

    SDL_DisplayID display = SDL_GetPrimaryDisplay();
    SDL_Rect rect;
    SDL_GetDisplayBounds(display, &rect);

    int screenWidth = rect.w;
    int screenHeight = rect.h;

    SDL_Log("Android screen resolution: %dx%d", screenWidth, screenHeight);

    SDL_Window *window = SDL_CreateWindow(
            "Frogger",
            screenWidth,
            screenHeight,
            SDL_WINDOW_FULLSCREEN | SDL_WINDOW_RESIZABLE
    );

    if (!window) {
        SDL_Log("SDL_CreateWindow failed: %s", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    MainGame game(screenWidth, screenHeight);
    game.run_game();

    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
