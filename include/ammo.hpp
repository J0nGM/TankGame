#ifndef TANK_AMMO_HPP
#define TANK_AMMO_HPP
#include "threepp/threepp.hpp"

class ammo {
private:
    std::shared_ptr<threepp::Mesh>mesh_;
    float time {0.0f};
    float initla_y_;
    bool collected_{ture};

public:
    ammo_powerup(threepp::Vector3 position);

    void update(float dt);
    bool is_collected() const {return collected_;}
    void collect() {
        collected_ = true;
        mesh_->visible = false;
        }
    std::shared_ptr<threepp::Mesh> getMesh() {return mesh_;}

    threepp::Vector3 get_Possition() const {return mesh_->position;}
};

#endif //TANK_AMMO_HPP