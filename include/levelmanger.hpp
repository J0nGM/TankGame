#ifndef TANK_LEVELMANGER_HPP
#define TANK_LEVELMANGER_HPP

#include "threepp/threepp.hpp"
#include "landscape.hpp"
#include "landscape2.hpp"
#include "arenawalls.hpp"
#include "pickupmanager.hpp"
#include "enemymanager.hpp"
#include "obstecalelvl2.hpp"
#include "portalLVL2.hpp"
#include <memory>
#include <functional>

struct level_events {
    bool player_hit {false};
    int enemies_killed {0};
    bool portal_reached {false};
};

class level_manger {
private:
    //Level 1 configuration
    static constexpr int level1_powerups = 10;
    static constexpr int level1_ammo = 10;
    static constexpr float level1_spawn_range = 230.0f;
    static constexpr float level1_arena_walls_size_ = 246.0f;

    //Level 2 configuration
    static constexpr int level2_powerups = 12;
    static constexpr int level2_ammo = 12;
    static constexpr int level2_enemies = 8;
    static constexpr float level2_spawn_range = 365.0f;
    static constexpr float level2_arena_walls_size_ = 375.0f; //The walls are further out than the landscape

    static constexpr float pickup_height = 3.0f;

    static constexpr float portal_activate_radius_ {10.0f};

    threepp::Scene& scene_;
    int current_level_ {1};

    Landscape& landscape1_;
    std::unique_ptr<Landscape2> landscape2_;

    arena_walls arena_;
    pickup_manager& pickups_;
    enemy_manager& enemies_;
    obstacle_manger_lvl2 obstacles_;

    std::unique_ptr<portal_lvl2> portal_;

    std::function<threepp::Vector3(float, float, float)> random_pos_func_;

    void check_portal_spawn();


    threepp::Vector3 get_random_level1_position();
    threepp::Vector3 get_random_level2_position();

public:
    level_manger(
        threepp::Scene& scene,
        Landscape& landscape1,
        pickup_manager& pickups,
        enemy_manager& enemies,
        std::function<threepp::Vector3(float, float, float)> random_pos_func);

    void setup_level_1();
    void setup_level_2();
    void clean_current_level();

    void spawn_portal(const threepp::Vector3& position);
    void update_portal(float dt);
    bool is_near_portal(const threepp::Vector3& position) const;


    // Return events instead of taking bullets
    level_events update_level(float dt, threepp::Vector3& tank_pos);

    //Expose managers for game_manger to use
    pickup_manager& get_pickup_manager() { return pickups_; }
    enemy_manager& get_enemy_manager() { return enemies_; }
    Landscape& get_landscape() { return landscape1_; }

    bool all_trees_destroyed() const;
    bool enemies_all_destroyed() const;

    int get_current_level() const { return current_level_; }
    bool portal_active() const { return portal_ && portal_->is_activated(); }

    bool are_all_enemies_defeated() const {
        return enemies_.get_enemy_count() == 0;
    }

    bool check_wall_collision_sphere(const threepp::Vector3& center, float radius) const;
    bool check_barrier_collision_sphere(const threepp::Vector3& center, float radius) const;
};

#endif
