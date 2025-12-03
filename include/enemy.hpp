#ifndef TANK_ENEMY_HPP
#define TANK_ENEMY_HPP
#include "threepp/threepp.hpp"

class enemy {
private:
    std::shared_ptr<threepp::Mesh> mesh_;
    threepp::Vector3 position_;
    float shoot_timer_{0};
    const float shoot_intreval_{3.5};
    int hp_{1};
    bool is_destroyed{false};
    const float bullet_height_enemy_{2.0};


public:
    enemy(threepp::Vector3 position);

    void update(float dt);

    bool should_shoot();

    void take_damage();

    bool is_damaged() const { return is_destroyed; }

    threepp::Vector3 get_position() const { return position_; }
    std::shared_ptr<threepp::Mesh> get_mesh() const { return mesh_; }
    int get_health() const { return hp_; }
    float get_bullet_spawn_height() const { return bullet_height_enemy_; }
};

#endif //TANK_ENEMY_HPP
