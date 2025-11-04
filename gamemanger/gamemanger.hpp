#ifndef TANK_GAMEMANGER_HPP
#define TANK_GAMEMANGER_HPP

#include <threepp/threepp.hpp>
#include <vector>
#include <memory>
#include "tank.hpp"
#include "keycontrolls.hpp"
#include "landscape.hpp"
#include "camercontrolls.hpp"
#include "boost.hpp"
#include "bullet.hpp"

class game_manger {
private:
    threepp::Scene& scene_;
    Tank& tank_;
    Key_controlls& key_controlls_;
    Landscape& landscape_;
    Camera_follow& camera_follow_;

    std::vector<std::unique_ptr<power_up_boost>> powerups_;
    std::vector<std::unique_ptr<bullet>> bullets_;

public:
    game_manger(
        threepp::Scene& scene,
        Tank& tank,
        Key_controlls& key_controls,
        Landscape& land,
        Camera_follow& camera_follow);

    void setup_powerups(int num_powerups);
    void update(float dt);

private:
    void handle_tank_movement(float dt);
    void handle_shooting();
    void update_bullets(float dt);
    void cleanup_bullets();
    void handle_powerup_collisions();
    void bullet_collisions_with_tree();
};

#endif //TANK_GAMEMANGER_HPP
