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

class game_manger {
private:
    threepp::Scene& scene_;
    Tank& tank_;
    key_input_handler& key_input_;
    Camera_follow& camera_follow_;

    tank_movement tank_movement_;
    tank_attack tank_attack_;
    bullet_manager player_bullets_;

    pickup_manager pickups_;
    enemy_manager enemies_;
    level_manger level_mgr_;

    bool level_completed_ {false};
    int player_hp_ {8};
    bool game_over_ {false};

public:
    game_manger(
        threepp::Scene& scene,
        Tank& tank,
        key_input_handler& key_input,
        Camera_follow& camera_follow,
        Landscape& landscape1,
        std::function<threepp::Vector3(float, float, float)> random_pos_func);

    void update(float dt);
    void reset_tank_position();

    int get_current_level() const { return level_mgr_.get_current_level(); }
    bool is_level_completed() const { return level_completed_; }
    int get_player_hp() const { return player_hp_; }
    bool is_game_over() const { return game_over_; }

private:
    threepp::Vector3 random_position(float range_x = 400.0f, float y = 3.0f, float range_z = 400.0f);

    void handle_tank_movement(float dt);
    void handle_shooting();
};

#endif
