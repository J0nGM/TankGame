#include "levelmanger.hpp"
#include "collisionmanger.hpp"
#include <iostream>

using namespace threepp;

level_manger::level_manger(
    Scene &scene,
    Landscape &landscape1,
    pickup_manager &pickups,
    enemy_manager &enemies,
    std::function<Vector3(float, float, float)> random_pos_func)
    : scene_(scene),
      landscape1_(landscape1),
      pickups_(pickups),
      enemies_(enemies),
      random_pos_func_(random_pos_func) {
}

void level_manger::setup_level_1() {
    current_level_ = 1;

    //Cleans up level 2 if you decied to restart the game after finishing level 2
    if (portal_) {
        scene_.remove(*portal_->get_mesh());
        portal_.reset();
    }


    if (landscape2_) {
        scene_.remove(*landscape2_->groundMesh);
        for (auto &road: landscape2_->roads) {
            scene_.remove(*road);
        }
        landscape2_.reset();
    }
    obstacles_.clear_obstacles(scene_);

    //Restors level 1
    scene_.add(landscape1_.groundMesh);
    for (auto &road: landscape1_.roads) {
        scene_.add(road);
    }

    float landscape_size = 750.0f;
    landscape1_.spawn_trees(scene_, random_pos_func_, landscape_size, landscape_size);

    for (auto &tree: landscape1_.objects) {
        tree->visible = true;
        scene_.add(tree);
    }

    //Level 1
    arena_.add_walls_to_scene(scene_, level1_arena_walls_size_);//arnea size. Located in the hpp

    pickups_.clear(scene_);

    pickups_.spawn_powerups(scene_, level1_powerups, level1_spawn_range, level1_spawn_range, pickup_height);

    pickups_.spawn_ammo(scene_, level1_ammo, level1_spawn_range, level1_spawn_range, pickup_height);
}


void level_manger::setup_level_2() {
    current_level_ = 2;
    clean_current_level();

    //Chose to make a new landscape for level 2 that is based on sand terrain
    landscape2_ = std::make_unique<Landscape2>();
    scene_.add(landscape2_->groundMesh);
    for (auto &road: landscape2_->roads) {
        scene_.add(road);
    }

    arena_.add_walls_to_scene(scene_, level2_arena_walls_size_);

    obstacles_.spawn_barriers_randomly(scene_, random_pos_func_);
    obstacles_.add_to_scene(scene_);

    pickups_.spawn_powerups(scene_, level2_powerups, level2_spawn_range, level2_spawn_range, pickup_height);
    pickups_.spawn_ammo(scene_, level2_ammo, level2_spawn_range, level2_spawn_range, pickup_height);

    enemies_.spawn_enemies(scene_, level2_enemies, level2_spawn_range, level2_spawn_range);

    float landscape_size = 750.0f;
    landscape2_->spawn_trees(scene_, random_pos_func_, landscape_size, landscape_size);

    if (portal_) {
        portal_->get_mesh()->visible = false;
    }
}

void level_manger::clean_current_level() {
    for (auto &tree: landscape1_.objects) {
        scene_.remove(*tree);
    }

    scene_.remove(*landscape1_.groundMesh);

    for (auto &road: landscape1_.roads) {
        scene_.remove(*road);
    }

    obstacles_.clear_obstacles(scene_);
}

//The portal is only spawned once when all trees are destroyed. THis make sure of that
void level_manger::spawn_portal(const Vector3 &position) {
    if (!portal_) {
        portal_ = std::make_unique<portal_lvl2>(position);
        scene_.add(portal_->get_mesh());
        portal_->activate();
    }
}

void level_manger::update_portal(float dt) {
    if (portal_) {
        portal_->update(dt);
    }
}

bool level_manger::is_near_portal(const Vector3 &position) const {
    if (!portal_ || !portal_->is_activated()) {
        return false;
    }

    Vector3 portal_pos = portal_->get_position();
    float distance = collision_manager::calculate_distance(position, portal_pos);

    return distance < portal_activate_radius_;
}

level_events level_manger::update_level(float dt, Vector3 &tank_pos) {
    level_events events;

    pickups_.update(dt);

    if (current_level_ == 1) {
        check_portal_spawn();
    } else if (current_level_ == 2) {
        enemies_.update(dt, tank_pos, scene_);

        //Check if player was hit by enemy bullets
        events.player_hit = enemies_.check_player_hit(tank_pos);

        //Push tank if colliding with enemies
        enemies_.push_tank_on_collision(tank_pos);
    }

    update_portal(dt);

    if (is_near_portal(tank_pos)) {
        events.portal_reached = true;
    }

    return events;
}

void level_manger::check_portal_spawn() {
    if (all_trees_destroyed() && !portal_active()) {
        spawn_portal(Vector3(50, 5, 50));
    }
}

bool level_manger::all_trees_destroyed() const {
    for (const auto &tree: landscape1_.objects) {
        if (tree->visible) {
            return false;
        }
    }
    return true;
}

//Check collisions with walls in arena
bool level_manger::enemies_all_destroyed() const {
    return (current_level_ == 2) ? enemies_.all_destroyed() : false;
}

bool level_manger::check_wall_collision_sphere(const Vector3 &center, float radius) const {
    return collision_manager::check_wall_collision_sphere(center, radius, arena_);
}

bool level_manger::check_barrier_collision_sphere(const Vector3 &center, float radius) const {
    if (current_level_ != 2) return false;
    return collision_manager::check_barrier_collision_sphere(center, radius, obstacles_);
}
