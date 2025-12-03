#include "tankmovment.hpp"

using namespace threepp;

tank_movement::tank_movement(tank& tank_obj)
    : tank_(&tank_obj) {
}

void tank_movement::update(const key_input_handler::KeyState &input, float dt, float speed_multiplier) {
    //Movement direction
    int move_direction = 0;
    if (input.up) move_direction = 1;
    else if (input.down) move_direction = -1;

    //Acceleration
    if (move_direction != 0) {
        speed_ += acceleration_ * dt;
        if (speed_ > max_speed_) speed_ = max_speed_;
    } else {
        speed_ -= deceleration_ * dt;
        if (speed_ < 0.0f) speed_ = 0.0f;
    }

    //Apply boost multiplier
    float actual_speed = speed_ * speed_multiplier;

    //Move tank
    if (move_direction != 0) {
        tank_->translateX(-actual_speed * move_direction * dt);
    }

    //Rotation
    if (input.right) tank_->rotateY(-turn_speed_ * dt);
    if (input.left) tank_->rotateY(turn_speed_ * dt);

    //Decrease boost time when using boost
    if (input.space && boost_time_left_ > 0.0f) {
        boost_time_left_ -= dt;
        if (boost_time_left_ < 0.0f) boost_time_left_ = 0.0f;
    }
}

float tank_movement::get_boost_multiplier(bool boost_active) const {
    if (boost_active && boost_time_left_ > 0.0f) {
        return boost_multiplier_;
    }
    return 1.0f;
}

void tank_movement::add_boost() {
    boost_time_left_ += 2.5f; //Add 2.5 seconds of boost
}