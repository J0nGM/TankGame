#ifndef TANK_ENEMY_MANAGER_HPP
#define TANK_ENEMY_MANAGER_HPP

#include "threepp/threepp.hpp"
#include "enemy.hpp"
#include "bulletmanager.hpp"
#include <vector>
#include <memory>

class enemy_manager {
private:
    std::vector<std::unique_ptr<enemy> > enemies_;
    bullet_manager enemy_bullets_;
    static constexpr int enemies_count_{12};
    static constexpr float enemy_spawn_height_{7.5};
    static constexpr float enemy_hit_radius_{20.0};
    static constexpr float enemy_tank_push_distance_{20.0};
    static constexpr float enemy_bullet_speed_{150.0};
    static constexpr float enemy_tank_push_force_{2.0};

public:
    void update(float dt, const threepp::Vector3 &tank_pos, threepp::Scene &scene);

    void clear(threepp::Scene &scene);

    void spawn_enemies(threepp::Scene &scene, int count, float range_x, float range_z);

    void spawn_enemies_for_level(threepp::Scene &scene, int level);


    int check_bullet_hits(const std::vector<std::unique_ptr<bullet> > &player_bullets);

    bool check_player_hit(const threepp::Vector3 &tank_pos);

    void push_tank_on_collision(threepp::Vector3 &tank_pos);

    //To see when enemies are all destroyed
    int get_enemy_count() const {
        return static_cast<int>(enemies_.size());
    }

    void remove_dead_enemies(threepp::Scene &scene);

    bool all_destroyed() const;

    const std::vector<std::unique_ptr<enemy> > &get_enemies() const { return enemies_; }
};

#endif
