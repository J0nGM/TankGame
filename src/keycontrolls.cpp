#include "keycontrolls.hpp"

Key_controlls::Key_controlls(Object3D &obj) : obj_(&obj),
                                              initial_position_(obj.position),
                                              initial_rotation_(obj.quaternion) {
}

float Key_controlls::get_speed() const {
    return speed_;
}

int Key_controlls::get_direction_moved() const {
    if (key_state_.up) return 1;
    if (key_state_.down) return -1;
    return 0;
}


void Key_controlls::onKeyPressed(KeyEvent evt) {
    if (evt.key == Key::W) {
        key_state_.up = true;
    } else if (evt.key == Key::S) {
        key_state_.down = true;
    } else if (evt.key == Key::D) {
        key_state_.right = true;
    } else if (evt.key == Key::A) {
        key_state_.left = true;
    }
    //Space for å aktivere boosten
    else if (evt.key == Key::SPACE) {
        key_state_.space = true;

    } else if (evt.key == Key::R) {
        //Legger til en reset knapp for tanksen
        obj_->position.copy(initial_position_);
        obj_->quaternion.copy(initial_rotation_);
        std::cout << "Restarted position" << std::endl;
    }
}

void Key_controlls::onKeyReleased(KeyEvent evt) {
    if (evt.key == Key::W) {
        key_state_.up = false;
        key_state_.up = false;
    } else if (evt.key == Key::S) {
        key_state_.down = false;
    } else if (evt.key == Key::D) {
        key_state_.right = false;
    } else if (evt.key == Key::A) {
        key_state_.left = false;
    }
    else if (evt.key == Key::SPACE) {
        key_state_.space = false;
    }
}

void Key_controlls::update(float dt) {
    if (key_state_.space && boost_time_left_ > 0.0f) {
        boost_time_left_ -= dt;
        if (boost_time_left_ < 0.0f) boost_time_left_ = 0.0f;
        speed_multiplier_ = 4.0f;
        std::cout << "Boost is active! Time left: " << static_cast<int>(boost_time_left_) << " seconds." << std::endl;
    }
    else {
        speed_multiplier_ = 1.0f;
    }


    int move_Direction = 0;
    if (key_state_.up) move_Direction = 1;
    else if (key_state_.down) move_Direction = -1;

    float acctual_speed = speed_ * speed_multiplier_;

    // Acceleration and deceleration
    if (move_Direction != 0) {
        speed_ += accleration_ * dt;
        if (speed_ > max_Speed_) speed_ = max_Speed_;
    } else {
        speed_ -= deaccleration_ * dt;
        if (speed_ < 0.0f) speed_ = 0.0f;
    }

    Vector3 old_position = obj_->position;
    //bevegelse
    if (move_Direction != 0) obj_->translateX(-acctual_speed * move_Direction * dt);
    //rotasjon
    if (key_state_.right) obj_->rotateY(-angel_Speed_ * dt);
    if (key_state_.left) obj_->rotateY(angel_Speed_ * dt);

}

void Key_controlls::add_boost() {
    boost_collected_++;
    boost_time_left_ += boost_time_max_;
    std::cout << "Boost is collected and ready to be used" << boost_collected_ << std::endl;
}