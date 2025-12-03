#include "bulletmanager.hpp"

using namespace threepp;

void bullet_manager::spawn_bullet(
    Scene &scene,
    const Vector3 &position,
    const Vector3 &direction,
    float speed) {
    auto bullet_ptr = std::make_unique<bullet>(position, direction, speed);
    scene.add(bullet_ptr->get_mesh());
    bullets_.push_back(std::move(bullet_ptr));
}

void bullet_manager::update(float dt) {
    for (auto &bullet: bullets_) {
        if (bullet->is_active()) {
            bullet->update(dt);
        }
    }
}

void bullet_manager::cleanup(Scene &scene) {
    bullets_.erase(
        std::remove_if(bullets_.begin(), bullets_.end(),
                       [&](auto &bullet) {
                           if (!bullet->is_active()) {
                               scene.remove(*bullet->get_mesh());
                               return true;
                           }
                           return false;
                       }
        ),
        bullets_.end()
    );
}

void bullet_manager::clear(Scene &scene) {
    for (auto &bullet: bullets_) {
        scene.remove(*bullet->get_mesh());
    }
    bullets_.clear();
}
