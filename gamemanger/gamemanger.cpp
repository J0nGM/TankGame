#include "gamemanger.hpp"
#include "collision.hpp"
#include "gamemanger.hpp"
#include <cstdlib>
#include <cmath>
#include <iostream>

using namespace threepp;

game_manger::game_manger(
    Scene &scene,
    Tank &tank,
    Key_controlls &key_controls,
    Landscape &land,
    Camera_follow &camera_follow)
        : scene_(scene),
          tank_(tank),
          key_controlls_(key_controls),
          landscape_(land),
          camera_follow_(camera_follow) {
}

void game_manger::setup_powerups(int count) {
    for (int i = 0; i < count; i++) {
        float random_x = (rand() % 400) - 200;
        float random_z = (rand() % 400) - 200;

        auto powerup_boost = std::make_unique<power_up_boost>(Vector3(random_x, 3.0f, random_z));
        scene_.add(powerup_boost->getMesh());
        powerups_.push_back(std::move(powerup_boost));
    }
}

void game_manger::handle_tank_movement(float dt) {
    Vector3 old_position = tank_.position;
    key_controlls_.update(dt);

    Box3 bb;
    bb.setFromObject(tank_);
    if (collision::check_collision(bb, landscape_.objects)) {
        tank_.position = old_position;
    }
}

void game_manger::handle_shooting() {
    if (key_controlls_.want_to_shoot() && key_controlls_.can_shoot()) {
        Vector3 forward(0, 0, -1);
        //Fikk hjelp med AI for Quaternion delen her.
        forward.applyQuaternion(tank_.quaternion);

        //Found the code from the webiste (threejs.org/docs/#Quaternion)
        Quaternion rotation;
        rotation.setFromAxisAngle(Vector3(0, 1, 0), math::PI / 2);
        forward.applyQuaternion(rotation);

        Vector3 spawn_position = tank_.position;
        spawn_position.y += 7.0f;
        spawn_position.addScaledVector(forward, 5.0f);

        auto bullet_ptr = std::make_unique<bullet>(spawn_position, forward, 200.0f); //endre fart på bullet

        scene_.add(bullet_ptr->get_mesh());
        bullets_.push_back(std::move(bullet_ptr));

        key_controlls_.start_cooldown();
        key_controlls_.reset_shoot();

        std::cout << "Shoot" << std::endl;
    }
}

void game_manger::update_bullets(float dt) {
    for (auto& bullet : bullets_) {
        if (bullet->is_active()) {
            bullet->update(dt);
        }
    }
}

void game_manger::cleanup_bullets() {
    bullets_.erase(
        std::remove_if(bullets_.begin(), bullets_.end(),
            [&](auto& bullet) {
                if (!bullet->is_active()) {
                    scene_.remove(*bullet->get_mesh());
                    return true;
                }
                return false;
            }
        ),
        bullets_.end()
    );
}

void game_manger::handle_powerup_collisions() {
    Box3 bb;
    bb.setFromObject(tank_);

    Vector3 tank_center;
    bb.getCenter(tank_center);

    for (auto &powerup: powerups_) {
        if (!powerup->is_collcted()) {
            Vector3 powerup_pos = powerup->get_Position();
            float dx = tank_center.x - powerup_pos.x;
            float dz = tank_center.z - powerup_pos.z;
            float distance = std::sqrt(dx * dx + dz * dz);

            if (distance < 5.0f) {
                powerup->collect();
                key_controlls_.add_boost();
            }
        }
    }
}
//Fikk assistanse fra AI her
void game_manger::bullet_collisions_with_tree() {
    for (auto& bullet: bullets_) {
        if (!bullet->is_active()) continue;

        Vector3 bullet_pos = bullet->get_position();

        for (auto& tree: landscape_.objects) {
            Vector3 tree_pos = tree->position;

            float dx = bullet_pos.x - tree_pos.x;
            float dz = bullet_pos.z - tree_pos.z;
            float distance = std::sqrt(dx * dx + dz * dz);

            if (distance < 5.0f) {
                tree->visible=false;
                bullet->deactivate();
                std::cout << "Tree damaged" << std::endl;
                break;
            }
        }
    }
}


void game_manger::update(float dt) {
    handle_tank_movement(dt);
    handle_shooting();
    update_bullets(dt);
    cleanup_bullets();
    handle_powerup_collisions();
    bullet_collisions_with_tree();
    camera_follow_.update(dt);

    for (auto &powerup: powerups_) {
        if (!powerup->is_collcted()) {
            powerup->update(dt);
        }
    }
}

