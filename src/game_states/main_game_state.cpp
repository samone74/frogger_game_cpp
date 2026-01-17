#include "main_game_state.h"

#include "objects/sdl_context.h"


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
        (*frog)->set_y(ctx.height() - frog_rect.height);
    }
    timer->update();
    return std::nullopt;
}
