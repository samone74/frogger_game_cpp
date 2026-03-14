#include "game.h"

int main() {
    constexpr int screen_width = 600;
    constexpr int screen_height = 800;
    MainGame game(ScreenSize(screen_width, screen_height));
    game.run_game();
}
