#ifndef TANK_POWERUP1_HPP
#define TANK_POWERUP1_HPP
#include <threepp/threepp.hpp>


class power_up_boost {
private:
    std::shared_ptr<threepp::Mesh> mesh_;
    float time_ {0.0};
    float initial_y_;
    bool collected_ {false};

public:
    power_up_boost(threepp::Vector3 position);

    void update(float dt);

    bool is_collected() const { return collected_;}
    void collect() {
        collected_ = true;
        mesh_->visible = false;
    }

    std::shared_ptr<threepp::Mesh> getMesh() {return mesh_;}

    threepp::Vector3 get_Position() const { return mesh_->position; }

};
#endif //TANK_POWERUP1_HPP