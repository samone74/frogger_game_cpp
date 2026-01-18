#include "game.h"
#include "objects/sdl_context.h"

int main() {
     std::string name = "frogger";
     SdlContext context(name, 800, 600);
     run_game(context);
}
