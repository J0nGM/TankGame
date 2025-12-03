#ifndef TANK_TANKMOVMENT_HPP
#define TANK_TANKMOVMENT_HPP

#include "tank.hpp"
#include "keyinputhandler.hpp"

class tank_movement {
private:
    tank* tank_;
    float speed_{0.0};
    float boost_time_left_{0.0};

    static constexpr float max_speed_{80.0};
    static constexpr float acceleration_{60.0};
    static constexpr float deceleration_{120.0};
    static constexpr float turn_speed_{2.5};
    static constexpr float boost_multiplier_{4.0};

public:
    explicit tank_movement(tank& tank_obj);

    void update(const key_input_handler::KeyState& input, float dt, float speed_multiplier);

    float get_speed() const { return speed_; }
    float get_boost_time_left() const { return boost_time_left_; }
    float get_boost_multiplier(bool boost_active) const;

    void add_boost();
};

#endif