#include "pickupmanager.hpp"
#include "tankattack.hpp"
#include "tankmovment.hpp"
#include "collisionmanger.hpp"
#include <iostream>

using namespace threepp;

void pickup_manager::spawn_powerups(Scene& scene, int count, float range_x, float range_z, float height) {
    for (int i = 0; i < count; i++) {
        float random_x = (rand() % static_cast<int>(range_x * 2)) - range_x; //AI assisted in finding rand()
        float random_z = (rand() % static_cast<int>(range_z * 2)) - range_z;

        auto powerup = std::make_unique<power_up_boost>(Vector3(random_x, height, random_z));
        scene.add(powerup->getMesh());
        powerups_.push_back(std::move(powerup));
    }
}

void pickup_manager::spawn_ammo(Scene& scene, int count, float range_x, float range_z, float height) {
    for (int i = 0; i < count; i++) {
        float random_x = (rand() % static_cast<int>(range_x * 2)) - range_x;
        float random_z = (rand() % static_cast<int>(range_z * 2)) - range_z;

        auto ammo_pickup = std::make_unique<ammo>(Vector3(random_x, height, random_z));
        scene.add(ammo_pickup->getMesh());
        ammo_.push_back(std::move(ammo_pickup));
    }
}

void pickup_manager::update(float dt) {
    for (auto& powerup : powerups_) {
        if (!powerup->is_collected()) {
            powerup->update(dt);
        }
    }

    for (auto& ammo_pickup : ammo_) {
        if (!ammo_pickup->is_collected()) {
            ammo_pickup->update(dt);
        }
    }
}

void pickup_manager::check_collisions(const threepp::Vector3& tank_pos, tank_attack& attack, tank_movement& movement){
    for (auto& powerup : powerups_) {
        if (!powerup->is_collected()) {
            Vector3 powerup_pos = powerup->get_Position();
            float distance = collision_manager::calculate_distance(tank_pos, powerup_pos);

            if (distance < pickup_collection_radius_) {
                powerup->collect();
                movement.add_boost();
            }
        }
    }

    for (auto& ammo_pickup : ammo_) {
        if (!ammo_pickup->is_collected()) {
            Vector3 ammo_pos = ammo_pickup->get_Position();
            float distance = collision_manager::calculate_distance(tank_pos, ammo_pos);

            if (distance < pickup_collection_radius_) {
                ammo_pickup->collect();
                attack.add_ammo(ammo_pickup->get_ammo_amount());
            }
        }
    }
}


void pickup_manager::clear(Scene& scene) {
    for (auto& powerup : powerups_) {
        scene.remove(*powerup->getMesh());
    }
    powerups_.clear();

    for (auto& ammo_pickup : ammo_) {
        scene.remove(*ammo_pickup->getMesh());
    }
    ammo_.clear();
}