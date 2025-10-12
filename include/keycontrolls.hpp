

#ifndef TANK_KEYCONTROLLS_HPP
#define TANK_KEYCONTROLLS_HPP

#include <iostream>
#include <threepp/threepp.hpp>
#include "threepp/loaders/AssimpLoader.hpp"
#include <iostream>
#include "threepp/input/KeyListener.hpp"
#include <cmath>
#include   "threepp/loaders/AssimpLoader.hpp"

using namespace threepp;


class keycontrolls: public KeyListener {
private: Object3D* obj_;
    Vector3 initialPosition_;
    Quaternion initialRotation_;

public:keycontrolls(Object3D& obj)
        : obj_(&obj),
        initialPosition_(obj.position),
        initialRotation_(obj.quaternion)  {}


    void onKeyPressed(KeyEvent evt) override {
    if (evt.key == Key::W) {
        keyState_.up = true;
    } else if (evt.key == Key::S) {
        keyState_.down = true;
    } else if (evt.key == Key::D) {
        keyState_.right = true;
    } else if (evt.key == Key::A) {
        keyState_.left = true;
    }else if (evt.key == Key::R) { //Legger til en reset kanpp for tanksen
        obj_->position.copy(initialPosition_);
        obj_->quaternion.copy(initialRotation_);
    }

    }

    void onKeyReleased(KeyEvent evt) override {
        if (evt.key == Key::W) {
            keyState_.up = false;
        } else if (evt.key == Key::S) {
            keyState_.down = false;
        } else if (evt.key == Key::D) {
            keyState_.right = false;
        } else if (evt.key == Key::A) {
            keyState_.left = false;
        }
    }

    void update(float dt) {

        if (keyState_.up) {
            obj_->translateX(-speed_*dt);
        }
        if (keyState_.down) {
            obj_->translateX(speed_*dt);
        }
        if (keyState_.right) {
            obj_->rotateY(-angularSpeed_*dt);
        }
        if (keyState_.left) {
            obj_->rotateY(angularSpeed_*dt);
        }
    }
private:
    //Gir indikasjon på hvilken knapp som er trykket inn
    struct KeyState {
        bool up = false;
        bool down = false;
        bool left = false;
        bool right = false;
    } keyState_;

    float speed_ = 10.0f; //Farten på W/S
    float angularSpeed_ = 2.0f; //Farten på A/D
};




#endif //TANK_KEYCONTROLLS_HPP

