#include "main_game.h"
#include "../objects/frog.h"
#include "../objects/lanes.h"
#include "../objects/lives.h"
#include <iostream>
#include "../objects/car.h"
#include "../objects/night.h"
#include <experimental/random>
#include "../objects/night.h"

//TODO add lights for cars
//TODO making the levels (adding lanes and later adding night and lanes)
//TODO add start screen
//TODO add lost screen
//TODO add picture of frog

Game::Game(int screen_width, int screen_height): m_screen_width(screen_width), m_screen_height(screen_height) {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
        throw std::runtime_error("SDL_Init Error: " + std::string(SDL_GetError()));
    }
    TTF_Init();

    create_window();
    create_renderer();
    objects.push_back(std::make_unique<Frog>(20, m_screen_width, m_screen_height));
    objects.push_back(std::make_unique<Night>(m_screen_width, m_screen_height));
    objects.push_back(std::make_unique<Lanes>(m_screen_width, m_screen_height));
    create_cars();
    create_live_objects();
    m_key_down_events = objects[0]->get_key_down_map();
    m_key_up_events = objects[0]->get_key_up_map();
    font = TTF_OpenFont("assets/arial.ttf", 32);
    text_objects.push_back({m_renderer, font, "test", {0,0,0,0}, 100, 0});
    auto& text = text_objects.at(0);
    timer = std::make_unique<CountDownTimer>(
    [&text](const std::string& value) {
        text.set_text(value);
    },
    60);
}

void Game::create_window() {
    m_window = SDL_CreateWindow(
        "Frogger",
        m_screen_width, m_screen_height,
        0
    );

    if (!m_window) {
        std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        throw std::runtime_error("SDL_CreateWindow Error: " + std::string(SDL_GetError()));
    }
}

void Game::create_renderer() {
    m_renderer = SDL_CreateRenderer(m_window, nullptr);
    if (!m_renderer) {
        std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(m_window);
        SDL_Quit();
        throw std::runtime_error("SDL_CreateRenderer Error: " + std::string(SDL_GetError()));
    }
    SDL_SetRenderDrawBlendMode(m_renderer, SDL_BLENDMODE_BLEND);
}

void Game::run() {
    m_running = true;
    timer->start();

    while (m_running) {
        set_level();
        handle_events();
        update_objects();
        render();
        SDL_Delay(16); // ~60 FPS
    }
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);
    SDL_Quit();
}

void Game::handle_events() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_EVENT_QUIT)
            m_running = false;
        if (event.type == SDL_EVENT_KEY_DOWN) {
            if (m_key_down_events.contains(event.key.key)) {
                m_key_down_events.at(event.key.key)();
            }
            if (event.key.key == SDLK_ESCAPE) {
                m_running = false;
            }
            if (event.key.key == SDLK_P) {
                change_level(1);
            }
            if (event.key.key == SDLK_O) {
                change_level(-1);
            }
        }
        if (event.type == SDL_EVENT_KEY_UP) {
            if (m_key_up_events.contains(event.key.key)) {
                m_key_up_events.at(event.key.key)();
            }
        }
    }
}

void Game::update_objects() {
    auto frog = std::ranges::find_if(objects,[](const std::unique_ptr<ObjectBase>& obj) {
                      return obj->get_type() == ObjectBase::Type::Frog;
                  });
    const Rectangle& frog_rect = (*frog)->get_rect();
    for (auto &object: objects) {
        object->update();
        if (object->get_type() == ObjectBase::Type::Car) {
            if ( detect_colosion(object->get_rect(), frog_rect)) {
                (*frog)->set_y(m_screen_height - frog_rect.height);
                m_lives--;
                if (m_lives == 0) {
                    m_lives = 5;
                    change_level( -m_level + 1);
                    set_level();
                }
                remove_live_objects();
                create_live_objects();
                break;
            }
        }
    }
    if (frog_rect.y == 0) {
        change_level(1);
        frog = std::ranges::find_if(objects,[](const std::unique_ptr<ObjectBase>& obj) {
                      return obj->get_type() == ObjectBase::Type::Frog;
                  });
        (*frog)->set_y(m_screen_height - frog_rect.height);
    }
    timer->update();
}


void Game::draw_object_to_screen(DrawObject draw_object) {
    SDL_SetRenderDrawColor(m_renderer, draw_object.color.red, draw_object.color.green, draw_object.color.blue,
                           draw_object.color.transparency);
    SDL_FRect object_rect(draw_object.rectangle.x, draw_object.rectangle.y,
                          draw_object.rectangle.width, draw_object.rectangle.height);
    if (draw_object.fill) {
        SDL_RenderFillRect(m_renderer, &object_rect);
    }
    else {
        SDL_RenderRect(m_renderer, &object_rect);
    }
    for (const auto& text: text_objects)
    {SDL_RenderTexture(m_renderer, text.get_texture(), NULL, &text.get_rect());}
}

std::map<int, std::vector<DrawObject> > Game::get_draw_objects() {
    std::map<int, std::vector<DrawObject> > draw_objects_map;
    for (auto &object: objects) {
        for (const auto &objects_to_draw = object->draw(); auto &object_to_draw: objects_to_draw) {
            if (!draw_objects_map.contains(object_to_draw.layer)) {
                draw_objects_map.insert(std::pair<int, std::vector<DrawObject> >(object_to_draw.layer, {}));
            }
            draw_objects_map.at(object_to_draw.layer).push_back(object_to_draw);
        }
    }
    return draw_objects_map;
}

void Game::create_cars() {
    const int lane_height = m_screen_height / (10 + 2);
    const int margin = 10;
    const int car_height = lane_height - margin;
    for (int i = 1; i <= m_level; i++) {
        int dir = std::experimental::randint(0, 1) == 0 ? -1 : 1;
        int speed = dir * std::experimental::randint(1, 5);
        int y = m_screen_height / 2 - lane_height / 2 * (m_level) + (i - 1) * lane_height + margin / 2;
        int number_of_cars_in_lane = std::round(3.0 / std::abs(speed));
        int distance_between_cars = 2 * m_screen_height / number_of_cars_in_lane;
        for (int j = 0; j < number_of_cars_in_lane; j++) {
            int red = std::experimental::randint(0, 255);
            int green = std::experimental::randint(0, 255);
            int blue = std::experimental::randint(0, 255);
            Color color(red, green, blue, 255);
            int x = std::experimental::randint(j * distance_between_cars, distance_between_cars * (j + 1) - car_height * 2);
            objects.push_back(std::make_unique<Car>(x, y, speed, color, car_height * 2,
                                                    car_height, m_screen_width, m_screen_height));
        }
    }
}

void Game::set_level() {
    for (auto &object: objects) {
        object->change_level(m_level);
    }
}

void Game::change_level(const int level_increase) {
    m_level += level_increase;
    m_level = std::max(m_level, 1);
    std::erase_if(objects,
                  [](const std::unique_ptr<ObjectBase>& obj) {
                      return obj->get_type() == ObjectBase::Type::Car;
                  });
    create_cars();
    set_level();
}

bool Game::detect_colosion(const Rectangle& a, const Rectangle& b) {
        return a.x < b.x + b.width  &&
               a.x + a.width > b.x  &&
               a.y < b.y + b.height &&
               a.y + a.height > b.y;
}

void Game::create_live_objects() {
    for (int i = 1; i <= m_lives; i++) {
        objects.push_back(std::make_unique<Live>(5 * i));
    }
}

void Game::remove_live_objects() {
    std::erase_if(objects,
              [](const std::unique_ptr<ObjectBase>& obj) {
                  return obj->get_type() == ObjectBase::Type::Live;
              });
}


void Game::render() {
    SDL_SetRenderDrawColor(m_renderer, 0, 125, 0, 255);
    SDL_RenderClear(m_renderer);
    const auto &draw_objects_map = get_draw_objects();
    for (auto &draw_objects: draw_objects_map) {
        for (auto &draw_object: draw_objects.second) { draw_object_to_screen(draw_object); }
    }

}
