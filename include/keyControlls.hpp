

#ifndef TANK_KEYCONTROLLS_HPP
#define TANK_KEYCONTROLLS_HPP

#include <iostream>
#include <threepp/threepp.hpp>
#include "threepp/loaders/AssimpLoader.hpp"
using namespace threepp;

/*class TankKeyControls: public KeyListener {

public:
    void onKeyPressed(KeyEvent) override;

};*/

class key_controller {
public:
    // ... your methods ...

private:
    Object3D* obj_;
    std::map<int, bool> keyState_;
    float speed_;
    float angularSpeed_;
};

#endif //TANK_KEYCONTROLLS_HPP


#endif //TANK_KEYCONTROLLS_HPP