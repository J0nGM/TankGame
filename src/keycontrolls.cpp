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
    else if (evt.key == Key::SPACE) {
        use_boost();
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
}

void Key_controlls::update(float dt) {
    if (boost_timer_ > 0.0f) {
        boost_timer_ -= dt;

        if (boost_timer_ <= 0.0f) {
            speed_multiplier_ = 1.0f;
            std::cout << "Boost has ended" << std::endl;
        }
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

void Key_controlls::speed_boost_activated() {
    speed_multiplier_ = 2.0f;
    boost_timer_ = boost_duration_;
    std::cout << "Speed boost is activated!" << std::endl;
}

void Key_controlls::add_boost() {
    boost_collected_++;
    std::cout << "Boost is collected" << boost_collected_ << std::endl;
}
void Key_controlls::use_boost() {
        if (boost_timer_ > 0.0f) {
            std::cout << "Boost is already active, cannot collect another" << std::endl;
            return;
        }
        if (boost_collected_ <= 0) {
            std::cout << "No boosts are available" << std::endl;
            return;
        }

        boost_collected_--;
        speed_multiplier_ = 2.0f;
        boost_timer_ = boost_duration_;
        std::cout << "Speed boost is activated, remainging boosts: " << boost_collected_ << std::endl;
}