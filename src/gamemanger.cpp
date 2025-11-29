#include "gamemanger.hpp"
#include "collisionmanger.hpp"
#include <cstdlib>
#include <iostream>

using namespace threepp;

game_manger::game_manger(
    Scene& scene,
    Tank& tank,
    key_input_handler& key_input,
    Camera_follow& camera_follow,
    Landscape& landscape1,
    std::function<Vector3(float, float, float)> random_pos_func)
    : scene_(scene),
      tank_(tank),
      key_input_(key_input),
      camera_follow_(camera_follow),
      tank_movement_(tank),
      tank_attack_(),
      player_bullets_(),
      pickups_(),
      enemies_(),
      level_mgr_(scene, landscape1, pickups_, enemies_, random_pos_func) {

    level_mgr_.setup_level_1();
}
Vector3 game_manger::random_position(float range_x, float y, float range_z) {
    float random_x = (rand() % static_cast<int>(range_x)) - (range_x / 2);
    float random_z = (rand() % static_cast<int>(range_z)) - (range_z / 2);
    return Vector3(random_x, y, random_z);
}

void game_manger::reset_tank_position() {
    tank_.position.set(0, 5, 0);
    tank_.quaternion.set(0, 0, 0, 1);
}

void game_manger::handle_tank_movement(float dt) {
    Vector3 old_position = tank_.position;

    const auto& keys = key_input_.get_keys();
    bool boost_active = keys.space;
    float boost_mult = tank_attack_.get_boost_multiplier(boost_active);

    tank_movement_.update(keys, dt, boost_mult);

    Box3 bb;
    bb.setFromObject(tank_);

    if (level_mgr_.check_wall_collision(bb)) {
        tank_.position.copy(old_position);
    }

    if (level_mgr_.get_current_level() == 2) {
        if (level_mgr_.check_barrier_collision(bb)) {
            tank_.position.copy(old_position);
        }
    }
}

void game_manger::handle_shooting() {
    const auto& keys = key_input_.get_keys();

    if (keys.e && tank_attack_.can_shoot()) {
        Vector3 spawn_pos = tank_.position;
        spawn_pos.y += 6.0f;

        Vector3 forward(-1, 0, 0); // Tank's forward direction
        forward.applyQuaternion(tank_.quaternion);
        forward.normalize();

        player_bullets_.spawn_bullet(scene_, spawn_pos, forward, 200.0f);
        tank_attack_.use_ammo();
        tank_attack_.start_cooldown();
    }
}

void game_manger::update(float dt) {
    if (game_over_) return;

    const auto& keys = key_input_.get_keys();
    if (keys.r) {
        reset_tank_position();
    }

    tank_attack_.update(dt);
    handle_tank_movement(dt);
    handle_shooting();

    Vector3 tank_center = tank_.position;
    tank_center.y = 3.0f;

    // Update level and get events
    auto events = level_mgr_.update_level(dt, tank_center);

    // Handle player damage
    if (events.player_hit) {
        player_hp_--;
        std::cout << "Player hit! HP: " << player_hp_ << std::endl;

        if (player_hp_ <= 0) {
            game_over_ = true;
            std::cout << "Game Over!" << std::endl;
        }
    }

    // Check powerup collisions HERE (not in level_manger)
    level_mgr_.get_pickup_manager().check_collisions(tank_center, tank_attack_);

    // Check bullet collisions HERE
    if (level_mgr_.get_current_level() == 1) {
        // Check player bullets vs trees
        for (auto& bullet : player_bullets_.get_bullets()) {
            if (bullet->is_active()) {
                Vector3 bullet_pos = bullet->get_position();

                if (collision_manager::check_bullet_tree_collision(
                    bullet_pos, level_mgr_.get_landscape().objects)) {
                    bullet->deactivate();
                }
            }
        }
    } else if (level_mgr_.get_current_level() == 2) {
        // Check player bullets vs enemies
        int enemies_killed = level_mgr_.get_enemy_manager().check_bullet_hits(
            player_bullets_.get_bullets());

        if (enemies_killed > 0) {
            std::cout << "Enemies killed: " << enemies_killed << std::endl;
        }
    }

    // Handle portal transition
    if (events.portal_reached && level_mgr_.get_current_level() == 1) {
        std::cout << "Entering Level 2..." << std::endl;
        level_mgr_.setup_level_2();
        reset_tank_position();
    }

    player_bullets_.update(dt);
    player_bullets_.cleanup(scene_);

    camera_follow_.update(dt);
}