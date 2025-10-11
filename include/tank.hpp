#include <iostream>
#include "threepp/input/KeyListener.hpp"
#include <cmath>
#include   "threepp/loaders/AssimpLoader.hpp"

using namespace threepp;
#ifndef EXAM_TANK_HPP
#define EXAM_TANK_HPP

/*
class key_controller: public KeyListener {

public:
    key_controller(Object3D& obj)
        : obj_(&obj) {}
    void onKeyPressed(KeyEvent evt) override {
        if (evt.key == Key::W) {
            keyState_.up = true;
        } else if (evt.key == Key::S) {
            keyState_.down = true;
        } else if (evt.key == Key::D) {
            keyState_.right = true;
        } else if (evt.key == Key::A) {
            keyState_.left = true;
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
            obj_->translateZ(-speed_*dt);
        }
        if (keyState_.down) {
            obj_->translateZ(speed_*dt);
        }
        if (keyState_.right) {
            obj_->rotateY(-angularSpeed_*dt);
        }
        if (keyState_.left) {
            obj_->rotateY(angularSpeed_*dt);
        }
    }



};
*/

#endif //EXAM_TANK_HPP