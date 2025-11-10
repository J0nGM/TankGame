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
            float distance = calcualte_distance(tank_center, ammo_pos);

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
            float distance = calcualte_distance(bullet_pos, tree_pos);

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
    float distance_ = calcualte_distance(tank_center, portal_pos);

    if (distance_ < 10.0f && portal_->is_activated()) {
        load_level_2();
    }
}
//Got some help from AI for the clean level function
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


void game_manger::update(float dt) {
    handle_tank_movement(dt);
    handle_shooting();
    update_bullets(dt);
    cleanup_bullets();
    handle_powerup_collisions();
    handle_ammo_collisions();
    bullet_collisions_with_tree();
    check_portal_spawn();
    portal_entry();

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
