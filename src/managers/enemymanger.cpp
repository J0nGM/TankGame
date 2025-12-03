#include "enemymanager.hpp"
#include "collisionmanger.hpp"
#include "bulletmanager.hpp"
#include <cstdlib>
#include <iostream>

using namespace threepp;

void enemy_manager::spawn_enemies(Scene& scene, int count, float range_x, float range_z) {
    for (int i = 0; i < count; i++) {
        float random_x = (rand() % static_cast<int>(range_x * 2)) - range_x;
        float random_z = (rand() % static_cast<int>(range_z * 2)) - range_z;

        auto enemy_ptr = std::make_unique<enemy>(Vector3(random_x, enemy_spawn_height_, random_z));
        scene.add(enemy_ptr->get_mesh());
        enemies_.push_back(std::move(enemy_ptr));
    }
}

void enemy_manager::spawn_enemies_for_level(Scene& scene, int level) {
    if (level == 2) {
        spawn_enemies(scene, enemies_count_, 700.0f, 700.0f); //Amount of enemies and the size of the arena
    }
}
void enemy_manager::update(float dt, const Vector3& tank_pos, Scene& scene) {
    for (auto& enemy : enemies_) {
        if (!enemy->is_damaged()) {
            enemy->update(dt);

            //Helps to aim at the player. There is an auto aim to make it a littel harder
            //Ai helped me here.
            if (enemy->should_shoot()) {
                Vector3 enemy_pos = enemy->get_position();
                Vector3 direction = tank_pos;
                direction.sub(enemy_pos);
                direction.y = 0;
                direction.normalize();

                //Where to spawn the bullet for the enemies
                Vector3 spawn_pos = enemy_pos;
                spawn_pos.y += enemy->get_bullet_spawn_height();

                enemy_bullets_.spawn_bullet(scene, spawn_pos, direction, enemy_bullet_speed_);
            }
        }
    }

    enemy_bullets_.update(dt);
    enemy_bullets_.cleanup(scene);
}

int enemy_manager::check_bullet_hits(const std::vector<std::unique_ptr<bullet>>& player_bullets) {
    int hits = 0;

    for (auto& bullet : player_bullets) {
        if (!bullet->is_active()) continue;

        Vector3 bullet_pos = bullet->get_position();

        for (auto& enemy : enemies_) {
            if (enemy->is_damaged()) continue;

            Vector3 enemy_pos = enemy->get_position();

            //Bullets have a hit radius of 20 of the tank
            float distance = collision_manager::calculate_distance(bullet_pos, enemy_pos);
            if (distance < enemy_hit_radius_) {
                bullet->deactivate();
                enemy->take_damage();
                hits++;
                break;
            }
        }
    }

    return hits;
}


bool enemy_manager::check_player_hit(const Vector3& tank_pos) {
    for (auto& bullet : enemy_bullets_.get_bullets()) {
        if (!bullet->is_active()) continue;

        Vector3 bullet_pos = bullet->get_position();
        float distance = collision_manager::calculate_distance(tank_pos, bullet_pos);

        if (distance < 5.0f) {
            bullet->deactivate();
            return true;
        }
    }
    return false;
}

void enemy_manager::push_tank_on_collision(Vector3& tank_pos) {
    for (auto& enemy : enemies_) {
        if (enemy->is_damaged()) continue;

        Vector3 enemy_pos = enemy->get_position();
        float distance = collision_manager::calculate_distance(tank_pos, enemy_pos);

        //Tried to create a "soft" collision when it collieds
        if (distance < enemy_tank_push_distance_) {
            Vector3 push_direction = tank_pos - enemy_pos;
            push_direction.y = 0;
            push_direction.normalize();
            tank_pos.addScaledVector(push_direction, enemy_tank_push_force_);
        }
    }
}


bool enemy_manager::all_destroyed() const {
    for (const auto& enemy : enemies_) {
        if (!enemy->is_damaged()) {
            return false;
        }
    }
    return true;
}

void enemy_manager::remove_dead_enemies(Scene& scene) {
    enemies_.erase(
        std::remove_if(enemies_.begin(), enemies_.end(),
            [&scene](const std::unique_ptr<enemy>& enemy) {
                if (enemy->is_damaged()) {
                    scene.remove(*enemy->get_mesh());
                    return true;
                }
                return false;
            }),
        enemies_.end()
    );
}

void enemy_manager::clear(Scene& scene) {
    for (auto& enemy : enemies_) {
        scene.remove(*enemy->get_mesh());
    }
    enemies_.clear();
    enemy_bullets_.clear(scene);
}