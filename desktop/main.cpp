#include "game.h"

int main() {
    constexpr int screen_width = 800;
    constexpr int screen_height = 600;
    MainGame game(ScreenSize(screen_width, screen_height));
    game.run_game();
}
