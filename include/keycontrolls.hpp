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
        bool space {false};
    } key_state_;

    float speed_ {0.0f};
    float max_Speed_ {40.0f}; //Farten på W/S
    float accleration_ {10.0f};
    float deaccleration_ {30.0f};
    float angel_Speed_ {2.5f}; //Farten på A/D

    float boost_time_left_ {0.0f};
    float boost_time_max_ {5.0f};

    //for powerupen
    float speed_multiplier_ {1.0f};//For å kunne endre farten ved powerups
    float boost_timer_ {0.0f};
    float boost_duration_ {5.0f};

    int boost_collected_ {0};

public:
    Key_controlls(Object3D &obj);

    //For å få delay på kamera, som jeg kan skal bruke i camercontrolls.hpp
    float get_speed() const;

    int get_direction_moved() const;

    void onKeyPressed(KeyEvent evt) override;

    void onKeyReleased(KeyEvent evt) override;

    void update(float dt);

    void speed_boost_activated();

    void add_boost();
    void use_boost();
    int get_collected_boosts() const { return boost_collected_; }
    bool has_activated_boost() const { return boost_timer_ > 0.0f;}
};
#endif //TANK_KEYCONTROLLS_HPP
