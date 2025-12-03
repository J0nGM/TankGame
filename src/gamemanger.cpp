#include "gamemanger.hpp"
#include "collisionmanger.hpp"
#include "imguihandler.hpp"
#include <cstdlib>
#include <iostream>

using namespace threepp;

game_manger::game_manger(
    Scene &scene,
    tank &tank,
    key_input_handler &key_input,
    Camera_follow &camera_follow,
    Landscape &landscape1,
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

    trail_manager_ = std::make_unique<trail_manager>(&scene_);

    // Add sphere to the tank for collision
    /*auto sphereGeom = threepp::SphereGeometry::create(collision_radius_, 16, 16);
    auto sphereMat = threepp::LineBasicMaterial::create();
    sphereMat->color = 0x00ff00;  // Green
    auto wireframe = threepp::WireframeGeometry::create(*sphereGeom);
    sphereHelper_ = threepp::LineSegments::create(wireframe, sphereMat);

    //To make the sphere around the tank visible
    scene_.add(sphereHelper_);*/
}

void game_manger::reset_tank_position() {
    tank_.position.set(0, tank_spawn_height_, 0);
    tank_.quaternion.set(0, 0, 0, 1);
}

void game_manger::handle_tank_movement(float dt) {
    Vector3 old_position = tank_.position;

    const auto &keys = key_input_.get_keys();
    bool boost_active = keys.space;
    float boost_mult = tank_movement_.get_boost_multiplier(boost_active);

    tank_movement_.update(keys, dt, boost_mult);

    Vector3 tank_center = tank_.position;

    //Wall collision
    if (level_mgr_.check_wall_collision_sphere(tank_center, collision_radius_)) {
        tank_.position.copy(old_position);
    }

    //Tree collision only for level 1
    if (level_mgr_.get_current_level() == 1) {
        threepp::Box3 tank_box;
        tank_box.setFromCenterAndSize(tank_center, threepp::Vector3(16, 10, 16));

        if (collision_manager::check_tree_collision(tank_box, level_mgr_.get_landscape().objects)) {
            tank_.position.copy(old_position);
        }
    }

    //Barrier collision only for level 2
    if (level_mgr_.get_current_level() == 2) {
        if (level_mgr_.check_barrier_collision_sphere(tank_center, collision_radius_)) {
            tank_.position.copy(old_position);
        }
    }
}

void game_manger::handle_shooting() {
    const auto &keys = key_input_.get_keys();

    if (keys.e && tank_attack_.can_shoot()) {
        Vector3 spawn_pos = tank_.position;
        spawn_pos.y += bullet_spawn_height_offset_;

        //From threepp examples, to get the forward direction of the tank
        Vector3 forward(-1, 0, 0); // Tank's forward direction
        forward.applyQuaternion(tank_.quaternion);
        forward.normalize();

        player_bullets_.spawn_bullet(scene_, spawn_pos, forward, tank_bullet_speed_);
        tank_attack_.use_ammo();
        tank_attack_.start_cooldown();
    }
}

void game_manger::restart_game() {
    game_over_ = false;
    victory_ = false;
    player_hp_ = 10;

    enemies_.clear(scene_);
    pickups_.clear(scene_);
    player_bullets_.cleanup(scene_);

    reset_tank_position();
    trail_manager_ = std::make_unique<trail_manager>(&scene_);

    level_mgr_.setup_level_1();
}

void game_manger::handle_menus(imgui_handler &imgui, bool &should_quit) {
    if (game_over_) {
        bool restart = false;
        bool quit = false;
        imgui.game_over_menu(restart, quit);

        if (restart) {
            restart_game();
        }
        if (quit) {
            should_quit = true;
        }
    }

    if (victory_) {
        bool restart = false;
        bool quit = false;
        imgui.victory_menu(restart, quit);

        if (restart) {
            restart_game();
        }
        if (quit) {
            should_quit = true;
        }
    }
}

void game_manger::update(float dt) {
    if (game_over_ || victory_) {
        return;
    }

    const auto &keys = key_input_.get_keys();
    if (keys.r) {
        reset_tank_position();
    }

    tank_attack_.update(dt);
    handle_tank_movement(dt);
    handle_shooting();

    Vector3 tank_center = tank_.position;
    tank_center.y = tank_collision_center_height_;

    auto events = level_mgr_.update_level(dt, tank_center);

    //Spawns trail when the tank is moving so that you can see the movement
    //AI assisted me a little with this part
    if (tank_movement_.get_speed() > min_speed_for_trail_) {
        //Only spawns when the tank moves
        time_since_last_trail_ += dt;
        if (time_since_last_trail_ >= trail_spawn_interval_) {
            //AI assisted me here. Was struggling to get the right direction for the trail
            Vector3 right(0, 0, 1);
            right.applyQuaternion(tank_.quaternion); //Rotation
            right.normalize();
            trail_manager_->add_trail(tank_.position, right);
            time_since_last_trail_ = 0.0f;
        }
    }

    trail_manager_->update(dt);

    //For visualtion of collision sphere
    //sphereHelper_->position.copy(tank_.position);

    //The damage that the tank/player takes
    if (events.player_hit) {
        player_hp_--;

        if (player_hp_ <= 0) {
            game_over_ = true;
        }
    }

    //Powerup pickup
    level_mgr_.get_pickup_manager().check_collisions(tank_center, tank_attack_, tank_movement_);

    //Had some major issue with this part, got some assistance from AI to make it work
    //Level 1 when you are shooting the trees
    if (level_mgr_.get_current_level() == 1) {
        for (auto &bullet: player_bullets_.get_bullets()) {
            if (bullet->is_active()) {
                Vector3 bullet_pos = bullet->get_position();

                if (collision_manager::check_bullet_tree_collision(bullet_pos, level_mgr_.get_landscape().objects)) {
                    bullet->deactivate();
                }
            }
        }
    }
    //Level 2 when you are shooting the enemies
    else if (level_mgr_.get_current_level() == 2) {
        int enemies_killed = level_mgr_.get_enemy_manager().check_bullet_hits(
            player_bullets_.get_bullets());

        if (enemies_killed > 0) {
            level_mgr_.get_enemy_manager().remove_dead_enemies(scene_);
        }

        //Check collision with enemies for instant death
        for (const auto &enemy: enemies_.get_enemies()) {
            if (!enemy->is_damaged()) {
                threepp::Vector3 enemy_pos = enemy->get_position();
                float dx = tank_center.x - enemy_pos.x;
                float dz = tank_center.z - enemy_pos.z;
                float distance = std::sqrt(dx * dx + dz * dz);

                if (distance < 15.0f) {
                    game_over_ = true;
                    break;
                }
            }
        }

        int enemy_count = level_mgr_.get_enemy_manager().get_enemy_count();

        if (enemy_count == 0) {
            victory_ = true;
        }
    }

    //For when entering the portal to go to level 2
    if (events.portal_reached && level_mgr_.get_current_level() == 1) {
        level_mgr_.setup_level_2();
        reset_tank_position();
    }

    player_bullets_.update(dt);
    player_bullets_.cleanup(scene_);

    camera_follow_.update(dt);
}
