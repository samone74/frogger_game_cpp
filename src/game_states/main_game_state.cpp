#include "main_game_state.h"

#include "objects/sdl_context.h"
#include <experimental/random>
#include <iostream>

#include "objects/color.h"
#include "objects/game_objects/car.h"
#include "objects/game_objects/count_down_timer.h"
#include "objects/game_objects/frog.h"
#include "objects/game_objects/lanes.h"
#include "objects/game_objects/lives.h"

MainGameState::MainGameState(const SdlContext &ctx) {
    objects.push_back(std::make_unique<Lanes>(ctx.screen_size()));
    create_cars(ctx);
    create_live_objects();
    objects.push_back(std::make_unique<Frog>(frog_size, ctx));
    m_key_down_events = objects.back()->get_key_down_map();
    m_key_up_events = objects.back()->get_key_up_map();
    objects.push_back(std::make_unique<CountDownTimer>(ctx, game_time));
}

TransitionRequest MainGameState::handle_event(const SdlContext &ctx, const SDL_Event &event) {
    switch (event.type) {
    case SDL_EVENT_QUIT: {
        return Transition::quit();
    }
    case SDL_EVENT_KEY_DOWN: {
        if (event.key.repeat) {
            return std::nullopt;
        }
        if (m_key_down_events.contains(event.key.key)) {
            m_key_down_events.at(event.key.key)();
            return std::nullopt;
        }
        if (event.key.key == SDLK_ESCAPE) {
            return Transition::quit();
        }
        if (event.key.key == SDLK_P) {
            change_level(ctx, 1);
            return std::nullopt;
        }
        if (event.key.key == SDLK_O) {
            change_level(ctx, -1);
            return std::nullopt;
        }
        return std::nullopt;
    }
    case SDL_EVENT_KEY_UP: {
        if (m_key_up_events.contains(event.key.key)) {
            m_key_up_events.at(event.key.key)();
            return std::nullopt;
        }
    }
    default: {
        return std::nullopt;
    }
    }
}

TransitionRequest MainGameState::update(const SdlContext &ctx) {
    auto frog = std::ranges::find_if(
        objects, [](const std::unique_ptr<ObjectBase> &obj) { return obj->get_type() == ObjectBase::Type::Frog; });
    const Rectangle &frog_rect = (*frog)->get_rect();
    for (auto &object : objects) {
        object->update();
        if (object->get_type() == ObjectBase::Type::Car) {
            if (detect_collision(object->get_rect(), frog_rect)) {
                (*frog)->set_y(static_cast<float>(ctx.height()) - frog_rect.height);
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
        if (m_level == max_level) {
            return Transition::switch_to(StateID::Win);
        }
        frog = std::ranges::find_if(
            objects, [](const std::unique_ptr<ObjectBase> &obj) { return obj->get_type() == ObjectBase::Type::Frog; });
        (*frog)->set_y(static_cast<float>(ctx.height()) - frog_rect.height);
    }
    // timer->update();
    return std::nullopt;
}

void MainGameState::create_cars(const SdlContext &ctx) {
    const int lane_height = ctx.height() / (10 + 2);
    constexpr int margin = 10;
    const int car_height = lane_height - margin;
    const int car_width = 2 * car_height;
    const int minimum_distance = car_width;
    for (int i = 1; i <= m_level; i++) {
        const int dir = std::experimental::randint(0, 1) == 0 ? -1 : 1;
        int speed = dir * std::experimental::randint(1, max_car_speed);
        // NOLINTNEXTLINE(readability-identifier-length)
        int y = ctx.height() / 2 - lane_height / 2 * (m_level) + (i - 1) * lane_height + margin / 2;
        const int number_of_cars_in_lane =
            static_cast<int>(std::round(max_car_in_lane / static_cast<float>(std::abs(speed))));
        const int length_for_car = ctx.width() / number_of_cars_in_lane;
        int x_prev = 0;
        for (int j = 0; j < number_of_cars_in_lane; j++) {
            const int red = std::experimental::randint(0, MAXCOLORVALUE);
            const int green = std::experimental::randint(0, MAXCOLORVALUE);
            const int blue = std::experimental::randint(0, MAXCOLORVALUE);
            Color color(red, green, blue, MAXCOLORVALUE);
            // NOLINTNEXTLINE(readability-identifier-length)
            const int x = std::experimental::randint(x_prev, length_for_car * (j + 1));
            x_prev = x + minimum_distance + car_width;
            objects.push_back(
                std::make_unique<Car>(Rectangle(static_cast<float>(x), static_cast<float>(y),
                                                static_cast<float>(car_width), static_cast<float>(car_height)),
                                      speed, color, ctx.screen_size()));
        }
    }
}

void MainGameState::set_level() const {
    for (const auto &object : objects) {
        object->change_level(m_level);
    }
}

void MainGameState::change_level(const SdlContext &ctx, const int level_increase) {
    m_level += level_increase;
    m_level = std::max(m_level, 1);
    std::erase_if(objects,
                  [](const std::unique_ptr<ObjectBase> &obj) { return obj->get_type() == ObjectBase::Type::Car; });
    create_cars(ctx);
    set_level();
}

void MainGameState::create_live_objects() {
    for (int i = 1; i <= m_lives; i++) {
        objects.push_back(std::make_unique<Live>(max_number_of_lives * i));
    }
}

void MainGameState::remove_live_objects() {
    std::erase_if(objects,
                  [](const std::unique_ptr<ObjectBase> &obj) { return obj->get_type() == ObjectBase::Type::Live; });
}

void MainGameState::render(SdlContext &ctx) {
    for (const auto &object : objects) {
        for (const auto &draw_object : object->get_draw_objects()) {
            draw_object->draw(ctx.renderer());
        }
    }
}

bool detect_collision(const Rectangle &left, const Rectangle &right) {
    return left.x < right.x + right.width && left.x + left.width > right.x && left.y < right.y + right.height &&
           left.y + left.height > right.y;
}
