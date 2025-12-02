#ifndef TANK_TANK_MOVEMENT_HPP
#define TANK_TANK_MOVEMENT_HPP

#include <threepp/threepp.hpp>
#include "keyinputhandler.hpp"

class tank_movement {
public:
    tank_movement(threepp::Object3D &tank);

    void update(const key_input_handler::KeyState &input, float dt, float speed_multiplier);

    void add_boost();

    float get_boost_multiplier(bool boost_pressed) const;

    float get_speed() const { return speed_; }

    //For the ImGui to show boost time left
    float get_boost_time_left() const { return boost_time_left_; }

private:
    threepp::Object3D *tank_;
    float speed_{0.0f};
    const float max_speed_{40.0f};
    const float acceleration_{15.0f};
    const float deceleration_{30.0f};
    const float turn_speed_{1.5f};

    //For the boost functionality
    int boost_collected_{0};
    float boost_time_left_{0.0f};
    const float boost_duration_{2.5f};
    const float boost_multiplier_{4.0f};//How much speed is increased when boost is active
};

#endif
