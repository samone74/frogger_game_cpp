#ifndef GAME_H
#define GAME_H
#include <SDL3/SDL.h>
#include <vector>
#include <memory>
#include <unordered_map>
#include <map>
#include <functional>
#include "objects/object_base.h"

class Game {
  public:
    Game(int screenWidth, int screenHeight);
    void run();
  private:
    const int m_screen_width;
    const int m_screen_height;
    bool m_running = false;
    SDL_Window* m_window = nullptr;
    SDL_Renderer* m_renderer = nullptr;
    std::vector<std::unique_ptr<ObjectBase>> objects;
    int m_level = 1;
    int m_lives = 5;
    void create_window();
    void create_renderer();
    void render();
    void update_objects();
    void handle_events();
    void draw_object_to_screen(DrawObject draw_object);
    std::map<int,  std::vector<DrawObject>> get_draw_objects();
    std::unordered_map<SDL_Keycode, std::function<void()> > m_key_down_events;
    std::unordered_map<SDL_Keycode, std::function<void()> > m_key_up_events;
    void create_cars();
    void set_level();
    void change_level(int level_increase);
    bool detect_colosion(const Rectangle& a, const Rectangle& b);
    void create_live_objects();
    void remove_live_objects();
};


#endif //GAME_H
