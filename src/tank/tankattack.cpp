#include "tankattack.hpp"

void tank_attack::add_ammo(int amount) {
    //So that we don't go over max ammo
    ammo_ += amount;
    if (ammo_ > max_ammo_) {
        ammo_ = max_ammo_;
    }
}

//check if cooldown is done and we have ammo left
bool tank_attack::can_shoot() const {
    return ammo_ > 0 && shoot_cooldown_ <= 0.0;
}

void tank_attack::start_cooldown() {
    shoot_cooldown_ = shoot_cooldown_time_;
}

void tank_attack::use_ammo() {
    //dont let ammo go negative
    if (ammo_ > 0) {
        ammo_--;
    }
}

void tank_attack::update(float dt) {
    //countdown the shoot cooldown timer
    if (shoot_cooldown_ > 0.0) {
        shoot_cooldown_ -= dt;
        if (shoot_cooldown_ < 0.0) {
            shoot_cooldown_ = 0.0;
        }
    }
}