#include "main_game_state.h"
#include "../objects/frog.h"
#include "../objects/lanes.h"
#include "../objects/lives.h"
#include <iostream>
#include "../objects/car.h"
#include "../objects/night.h"
#include "objects/sdl_context.h"
#include <experimental/random>

MainGameState::MainGameState(const SdlContext& ctx){

    objects.push_back(std::make_unique<Frog>(20, ctx.width(), ctx.height()));
    //objects.push_back(std::make_unique<Night>( ctx.width(), ctx.height()));
    objects.push_back(std::make_unique<Lanes>(ctx.width(), ctx.height()));
    create_cars(ctx);
    create_live_objects();
    m_key_down_events = objects[0]->get_key_down_map();
    m_key_up_events = objects[0]->get_key_up_map();
    text_objects.push_back({TextID::Level, "Test",50,50, {255,0,0,0}, 0});
    timer = std::make_unique<CountDownTimer>( [obj = &text_objects.at(0)](const std::string& s) { obj->set_text(s); }, 60);
    sprite_objects.push_back({R"(C:\Users\samzw\OneDrive\Documenten\GitHub\frogger_game_cpp\assets\sprites\frog.png)", 10,10,20,20,0});
}

TransitionRequest MainGameState::handle_event(const SdlContext& ctx, const SDL_Event& event) {
    if (event.type == SDL_EVENT_QUIT)
        return Transition::quit() ;
    if (event.type == SDL_EVENT_KEY_DOWN) {
        if (m_key_down_events.contains(event.key.key)) {
            m_key_down_events.at(event.key.key)();
        }
        if (event.key.key == SDLK_ESCAPE) {
            return Transition::quit();
        }
        if (event.key.key == SDLK_P) {
            change_level(ctx, 1);
            return std::nullopt ;
        }
        if (event.key.key == SDLK_O) {
            change_level(ctx, -1);
            return std::nullopt ;
        }
    }
    if (event.type == SDL_EVENT_KEY_UP) {
        if (m_key_up_events.contains(event.key.key)) {
            m_key_up_events.at(event.key.key)();
            return std::nullopt ;
        }
    }
    return std::nullopt;
}

TransitionRequest MainGameState::update(const SdlContext& ctx) {
    auto frog = std::ranges::find_if(objects,[](const std::unique_ptr<ObjectBase>& obj) {
                      return obj->get_type() == ObjectBase::Type::Frog;
                  });
    const Rectangle& frog_rect = (*frog)->get_rect();
    for (auto &object: objects) {
        object->update();
        if (object->get_type() == ObjectBase::Type::Car) {
            if ( detect_collision(object->get_rect(), frog_rect)) {
                (*frog)->set_y(ctx.height() - frog_rect.height);
                m_lives--;
                if (m_lives == 0) {
                    return Transition::switch_to(StateID::Lose);
                }
                remove_live_objects();
                create_live_objects();
                break;
            }
        }
    }
    if (frog_rect.y == 0) {
        change_level(ctx, 1);
        if ( m_level == 11)
            return Transition::switch_to(StateID::Win);
        frog = std::ranges::find_if(objects,[](const std::unique_ptr<ObjectBase>& obj) {
                      return obj->get_type() == ObjectBase::Type::Frog;
                  });
        (*frog)->set_y(ctx.height() - frog_rect.height);
    }
    timer->update();
    return std::nullopt;
}


std::map<int, std::vector<DrawObject>> MainGameState::get_draw_objects() {
    std::map<int, std::vector<DrawObject>> draw_objects_map;
    for (auto& object : objects) {
        auto objects_to_draw = object->draw();   // store the vector by value
        for (auto& object_to_draw : objects_to_draw) {
            draw_objects_map[object_to_draw.layer].push_back(object_to_draw);
        }
    }
    return draw_objects_map;
}


void MainGameState::create_cars(const SdlContext& ctx) {
    const int lane_height = ctx.height() / (10 + 2);
    const int margin = 10;
    const int car_height = lane_height - margin;
    for (int i = 1; i <= m_level; i++) {
        int dir = std::experimental::randint(0, 1) == 0 ? -1 : 1;
        int speed = dir * std::experimental::randint(1, 5);
        int y = ctx.height() / 2 - lane_height / 2 * (m_level) + (i - 1) * lane_height + margin / 2;
        int number_of_cars_in_lane = std::round(3.0 / std::abs(speed));
        int distance_between_cars = 2 * ctx.height() / number_of_cars_in_lane;
        for (int j = 0; j < number_of_cars_in_lane; j++) {
            int red = std::experimental::randint(0, 255);
            int green = std::experimental::randint(0, 255);
            int blue = std::experimental::randint(0, 255);
            Color color(red, green, blue, 255);
            int x = std::experimental::randint(j * distance_between_cars, distance_between_cars * (j + 1) - car_height * 2);
            objects.push_back(std::make_unique<Car>(x, y, speed, color, car_height * 2,
                                                    car_height, ctx.width(), ctx.height()));
        }
    }
}

void MainGameState::set_level() const
{
    for (auto &object: objects) {
        object->change_level(m_level);
    }
}

void MainGameState::change_level(const SdlContext& ctx, const int level_increase) {
    m_level += level_increase;
    m_level = std::max(m_level, 1);
    std::erase_if(objects,
                  [](const std::unique_ptr<ObjectBase>& obj) {
                      return obj->get_type() == ObjectBase::Type::Car;
                  });
    create_cars(ctx);
    set_level();
}

bool MainGameState::detect_collision(const Rectangle& a, const Rectangle& b) {
        return a.x < b.x + b.width  &&
               a.x + a.width > b.x  &&
               a.y < b.y + b.height &&
               a.y + a.height > b.y;
}

void MainGameState::create_live_objects() {
    for (int i = 1; i <= m_lives; i++) {
        objects.push_back(std::make_unique<Live>(5 * i));
    }
}

void MainGameState::remove_live_objects() {
    std::erase_if(objects,
              [](const std::unique_ptr<ObjectBase>& obj) {
                  return obj->get_type() == ObjectBase::Type::Live;
              });
}

void MainGameState::render(SdlContext& ctx) {
    const auto &draw_objects_map = get_draw_objects();
    for (auto &draw_objects: draw_objects_map) {
        for (auto &draw_object: draw_objects.second) { ctx.draw_object_to_screen(draw_object); }
    }
    for (auto &text_object: text_objects) {
        ctx.draw_text_to_screen(text_object);
    }
    for (auto &sprite_object: sprite_objects) {
        ctx.draw_sprite_to_screen(sprite_object);
    }
}
