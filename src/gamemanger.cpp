#include "gamemanger.hpp"
#include "collision.hpp"
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

//Created a randomfunction, got assistanse from AI
threepp::Vector3 game_manger::random_position(float range_x, float y, float range_z) {
    float random_x = (rand() % static_cast<int>(range_x)) - (range_x / 2);
    float random_z = (rand() % static_cast<int>(range_z)) - (range_z / 2);
    return Vector3(random_x, y, random_z);
}

void game_manger::setup_powerups(int count) {
    spawn_item_pickup(powerups_, count);
}

void game_manger::setup_ammo(int count) {
    spawn_item_pickup(ammo_, count);
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

void game_manger::handle_ammo_collisions() {
    Box3 bb;
    bb.setFromObject(tank_);
    Vector3 tank_center;
    bb.getCenter(tank_center);

    for (auto &ammo_pickup: ammo_) {
        if (!ammo_pickup->is_collected()) {
            Vector3 ammo_pos = ammo_pickup->get_Position();
            float distance = calculate_distance(tank_center, ammo_pos);

            if (distance < 5.0f) {
                ammo_pickup->collect();
                key_controlls_.add_ammo(ammo_pickup->get_ammo_amount());
                std::cout << "Shoot - Bullet: " << key_controlls_.get_ammo() << std::endl;
            }
        }
    }
}

void game_manger::handle_shooting() {
    if (key_controlls_.want_to_shoot() && key_controlls_.can_shoot()) {
        Vector3 forward(0, 0, -1);

        //Found the code exampel from the webiste (threejs.org/docs/#Quaternion)
        forward.applyQuaternion(tank_.quaternion);
        Quaternion rotation;
        rotation.setFromAxisAngle(Vector3(0, 1, 0), math::PI / 2);
        forward.applyQuaternion(rotation);

        Vector3 spawn_position = tank_.position;
        spawn_position.y += 7.0f;
        spawn_position.addScaledVector(forward, 5.0f);

        auto bullet_ptr = std::make_unique<bullet>(spawn_position, forward, 200.0f); //CHanges speed for the bullet

        scene_.add(bullet_ptr->get_mesh());
        bullets_.push_back(std::move(bullet_ptr));

        key_controlls_.use_ammo();
        key_controlls_.start_cooldown();
        key_controlls_.reset_shoot();

        std::cout << "Shoot" << std::endl;
    }
}

void game_manger::update_bullets(float dt) {
    for (auto &bullet: bullets_) {
        if (bullet->is_active()) {
            bullet->update(dt);
        }
    }
}

void game_manger::cleanup_bullets() {
    bullets_.erase(
        std::remove_if(bullets_.begin(), bullets_.end(),
                       [&](auto &bullet) {
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
                std::cout << "Boost collected" << std::endl;
            }
        }
    }
}

//Got assistens from AI to create this function
void game_manger::bullet_collisions_with_tree() {
    for (auto &bullet: bullets_) {
        if (!bullet->is_active()) continue;

        Vector3 bullet_pos = bullet->get_position();

        for (auto &tree: landscape_.objects) {
            if (!bullet->is_active()) continue;
            Vector3 tree_pos = tree->position;
            float distance = calculate_distance(bullet_pos, tree_pos);

            if (distance < 5.0f) {
                tree->visible = false;
                bullet->deactivate();
                std::cout << "Tree damaged" << std::endl;
                break;
            }
        }
    }
}

bool game_manger::all_trees_destroyed() const {
    for (const auto &tree: landscape_.objects) {
        if (tree->visible) {
            //If any trees are still visible
            return false;
        }
    }
    return true; //When all trees are gone
}

void game_manger::check_portal_spawn() {
    if (!portal_ && all_trees_destroyed()) {
        Vector3 portal_position(0, 5, 0);
        portal_ = std::make_unique<portal_lvl2>(portal_position);
        scene_.add(portal_->get_mesh());
        portal_->activate();

        std::cout << "Portal spawned!" << std::endl;
    }
}

void game_manger::portal_entry() {
    if (!portal_) return;
    if (current_level_ ==2) return; //So that I don't load the level multiple times when entering the portal

    Box3 bb;
    bb.setFromObject(tank_);
    Vector3 tank_center;
    bb.getCenter(tank_center);

    Vector3 portal_pos = portal_->get_position();
    float distance_ = calculate_distance(tank_center, portal_pos);

    if (distance_ < 10.0f && portal_->is_activated()) {
        load_level_2();
    }
}
//Got help from AI for the clean level function
void game_manger::clean_level() {
    for (auto &bullet: bullets_) {
        scene_.remove(*bullet->get_mesh());
    }
    bullets_.clear();

    for (auto &tree: landscape_.objects) {
        scene_.remove(*tree);
    }
    landscape_.objects.clear();

    for (auto &powerup: powerups_) {
        scene_.remove(*powerup->getMesh());
    }
    powerups_.clear();

    for (auto &ammo: ammo_) {
        scene_.remove(*ammo->getMesh());
    }
    ammo_.clear();

    scene_.remove(*landscape_.groundMesh);

    for (auto& road : landscape_.roads) {
        scene_.remove(*road);
    }

}

void game_manger::load_level_2() {
    level_completed_ = true;
    current_level_ = 2;
    clean_level();

    tank_.position.set(0, 5, 0);
    tank_.rotation.set(0, 0, 0);

    setup_powerups(7);
    setup_ammo(10);
    setup_enemies(5);

    auto ground_geometry = PlaneGeometry::create(750, 750);
    auto ground_material = MeshPhongMaterial::create();
    ground_material->color = Color(1.0f, 0.8f, 0.6f);

    level2_ground_ = Mesh::create(ground_geometry, ground_material);
    level2_ground_->rotation.x = -math::PI / 2;
    level2_ground_->position.y = -0.5f;
    level2_ground_->receiveShadow = true;
    scene_.add(level2_ground_);

    if (current_level_ == 2) {
        portal_->get_mesh()->visible = false; //so that the protal disspears when I etner level 2
    }
}
void game_manger::setup_enemies(int count) {
    for (int i = 0; i < count; i++) {
        const float random_x = (rand() % 400) - 200;
        const float random_z = (rand() % 400) - 200;

        auto enemy_ptr = std::make_unique<Enemy>(Vector3(random_x, 12.5f, random_z));
        scene_.add(enemy_ptr->get_mesh());
        enemies_.push_back(std::move(enemy_ptr));
    }
}

void game_manger::update_enemies(float dt) {
    for (auto& enemy : enemies_) {
        if (!enemy->is_damaged()) {
            enemy->update(dt);
        }
    }
}
//Got help from AI for this part
void game_manger::update_enemy_bullets(float dt) {
    for (auto& bullets : enemy_bullets_) {
        if (bullets->is_active()) {
            bullets->update(dt);
        }
    }
    enemy_bullets_.erase(
        std::remove_if(enemy_bullets_.begin(), enemy_bullets_.end(),
            [&](auto &bullets) {
                if (!bullets->is_active()) {
                    scene_.remove(*bullets->get_mesh());
                    return true;
                }
                return false;
            }
            ),
            enemy_bullets_.end()
            );
}

void game_manger::enemy_shooting() {
    for (auto& enemy : enemies_) {
        if (enemy->should_shoot()) {
            Vector3 enemy_pos = enemy->get_position();

            Vector3 direction = tank_.position;
            direction.sub(enemy_pos);
            direction.y = 0;
            direction.normalize();

            Vector3 spawn_position = enemy_pos;
            spawn_position.y += 6.0f;
            auto enemy_bullet_ptr = std::make_unique<bullet>(spawn_position, direction, 150.0f);
            scene_.add(enemy_bullet_ptr->get_mesh());
            enemy_bullets_.push_back(std::move(enemy_bullet_ptr));
        }
    }
}

void game_manger::check_player_hit() {
    if (game_over_) return;
    Box3 tank_bb;
    tank_bb.setFromObject(tank_);
    Vector3 tank_center;
    tank_bb.getCenter(tank_center);

    for (auto& bullet : enemy_bullets_) {
        if (!bullet->is_active()) continue;

        Vector3 bullet_pos = bullet->get_position();
        float distance = calculate_distance(tank_center, bullet_pos);

        if (distance < 5.0f) {
            bullet->deactivate();
            player_hp_--;
            for (int i = 0; i < player_hp_; i++) {
            }
            std::cout << "Player hit. HP: " << player_hp_ << std::endl;

            if (player_hp_ <= 0) {
                game_over_ = true;
                std::cout << "Game Over!" << std::endl;
            }
            break;
        }
    }

}

void game_manger::check_enemy_hit() {
    for (auto& bullet : bullets_) {
        if (!bullet->is_active()) continue;

        Vector3 bullet_pos = bullet->get_position();
        for (auto& enemy : enemies_) {
            if (enemy->is_damaged()) continue;

            Vector3 enemy_pos = enemy->get_position();
            float distance = calculate_distance(bullet_pos, enemy_pos);

            std::cout << "  Distance to enemy: " << distance << std::endl;
            if (distance < 15.0f) {
                enemy->take_damage();
                bullet->deactivate();
                break;
            }
        }
    }

}

void game_manger::check_enemy_collisions() {
    Box3 bb;
    bb.setFromObject(tank_);
    Vector3 tank_center;
    bb.getCenter(tank_center);

    for (auto& enemy : enemies_) {
        if (enemy->is_damaged()) continue;
        Vector3 enemy_pos = enemy->get_position();
        float distance = calculate_distance(tank_center, enemy_pos);

        if (distance<8.0f) {
            Vector3 push_direction = tank_center;
            push_direction.sub(enemy_pos);
            push_direction.y = 0;
            push_direction.normalize();

            tank_.position.addScaledVector(push_direction, 0.5f);
        }
    }
}

void game_manger::update(float dt) {
    if (game_over_) {
        return;
    }

    handle_tank_movement(dt);
    handle_shooting();
    update_bullets(dt);
    cleanup_bullets();
    handle_powerup_collisions();
    handle_ammo_collisions();
    bullet_collisions_with_tree();
    check_portal_spawn();
    portal_entry();

    if (current_level_ == 2) {
        update_enemies(dt);
        enemy_shooting();
        update_enemy_bullets(dt);
        check_player_hit();
        check_enemy_hit();
        check_enemy_collisions();

    }

    if (portal_) {
        portal_->update(dt);
    }
    camera_follow_.update(dt);

    for (auto &powerup: powerups_) {
        if (!powerup->is_collcted()) {
            powerup->update(dt);
        }
    }
    for (auto &ammo: ammo_) {
        if (!ammo->is_collected()) {
            ammo->update(dt);
        }
    }
}