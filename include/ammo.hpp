#ifndef TANK_AMMO_HPP
#define TANK_AMMO_HPP
#include "threepp/threepp.hpp"

class ammo {
private:
    std::shared_ptr<threepp::Mesh> mesh_;
    float lifetime_{0.0};
    float initla_y_; //Direction
    bool collected_{false};
    int amount_ammo_per_pickup_{2};

public:
    ammo(threepp::Vector3 position);

    void update(float dt);

    bool is_collected() const { return collected_; }

    void collect() {
        collected_ = true;
        mesh_->visible = false;
    }

    int get_ammo_amount() const { return amount_ammo_per_pickup_; }

    std::shared_ptr<threepp::Mesh> getMesh() { return mesh_; }
    threepp::Vector3 get_Position() const { return mesh_->position; }
};

#endif //TANK_AMMO_HPP
