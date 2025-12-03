#ifndef TANK_GAMEMANGER_HPP
#define TANK_GAMEMANGER_HPP

#include <threepp/threepp.hpp>
#include <memory>
#include "tank.hpp"
#include "keyinputhandler.hpp"
#include "tankattack.hpp"
#include "tankmovment.hpp"
#include "landscape.hpp"
#include "camercontrolls.hpp"
#include "bulletmanager.hpp"
#include "levelmanger.hpp"
#include "trailmanager.hpp"

class imgui_handler;

class game_manger {
private:
    threepp::Scene& scene_;
    tank& tank_;
    key_input_handler& key_input_;
    Camera_follow& camera_follow_;

    tank_movement tank_movement_;
    tank_attack tank_attack_;
    bullet_manager player_bullets_;

    pickup_manager pickups_;
    enemy_manager enemies_;
    level_manger level_mgr_;

    int player_hp_ {10};
    bool game_over_ {false};
    bool victory_ {false};

    //Tank config
    static constexpr float tank_spawn_height_ {5.0};
    static constexpr float tank_collision_center_height_ {3.0};

    //Bullet config
    static constexpr float bullet_spawn_height_offset_ {2.0};
    static constexpr float tank_bullet_speed_ {200.0};

    //Trail config
    std::unique_ptr<trail_manager>trail_manager_;
    float time_since_last_trail_ {0.0};
    static constexpr float trail_spawn_interval_ {0.1};
    static constexpr float min_speed_for_trail_ {0.3};

    //Radius of the sphere used for collision visualization
    std::shared_ptr<threepp::LineSegments> sphereHelper_;
    float collision_radius_ = 8.0;

public:
    game_manger(
        threepp::Scene& scene,
        tank& tank,
        key_input_handler& key_input,
        Camera_follow& camera_follow,
        Landscape& landscape1,
        std::function<threepp::Vector3(float, float, float)> random_pos_func);

    void update(float dt);
    void reset_tank_position();

    int get_current_level() const { return level_mgr_.get_current_level(); }
    int get_player_hp() const { return player_hp_; }
    bool is_game_over() const { return game_over_; }
    void handle_menus(imgui_handler& imgui, bool& should_quit);

    //For the Imgui display
    int get_ammo_count() const { return tank_attack_.get_ammo(); }
    float get_boost_time_left() const { return tank_movement_.get_boost_time_left(); }

private:
    void handle_tank_movement(float dt);
    void handle_shooting();
    void restart_game();
};

#endif