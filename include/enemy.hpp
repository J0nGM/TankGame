#ifndef TANK_ENEMY_HPP
#define TANK_ENEMY_HPP
#include "threepp/threepp.hpp"

class Enemy {
private:
    std::shared_ptr<threepp::Mesh> mesh_;
    threepp::Vector3 position_;
    float shoot_timer_{0};
    const float shoot_intreval_{2.0f};
    int hp_{1};
    bool is_destryd{false};

public:
    Enemy(threepp::Vector3 position);

    void update(float dt);

    bool should_shoot();

    void take_damage();

    bool is_damaged() const { return is_destryd; }

    threepp::Vector3 get_position() const { return position_; }
    std::shared_ptr<threepp::Mesh> get_mesh() const { return mesh_; }
    int get_health() const { return hp_; }
};

#endif //TANK_ENEMY_HPP
