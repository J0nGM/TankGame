#ifndef TANK_KEYCONTROLLS_HPP
#define TANK_KEYCONTROLLS_HPP

#include <iostream>
#include <threepp/threepp.hpp>
#include "threepp/loaders/AssimpLoader.hpp"
#include "threepp/input/KeyListener.hpp"
#include <cmath>

using namespace threepp;


class Key_controlls : public KeyListener {
private:
    Object3D *obj_;
    Vector3 initial_position_;
    Quaternion initial_rotation_;//Fiks dette

    //Gir indikasjon på hvilken knapp som er trykket inn
    struct key_state {
        bool up {false};
        bool down {false};
        bool left {false};
        bool right {false};
    } key_state_;

    float speed_ {0.0f};
    float max_Speed_ {40.0f}; //Farten på W/S
    float accleration_ {10.0f};
    float deaccleration_ {30.0f};

    float angel_Speed_ {2.5f}; //Farten på A/D

public:
    Key_controlls(Object3D &obj);

    //For å få delay på kamera, som jeg kan skal bruke i camercontrolls.hpp
    float get_speed() const;

    int get_direction_moved() const;

    void onKeyPressed(KeyEvent evt) override;

    void onKeyReleased(KeyEvent evt) override;

    void update(float dt);
};
#endif //TANK_KEYCONTROLLS_HPP
