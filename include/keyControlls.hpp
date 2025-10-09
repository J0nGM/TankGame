

#ifndef TANK_KEYCONTROLLS_HPP
#define TANK_KEYCONTROLLS_HPP

#include <iostream>
#include <threepp/threepp.hpp>
#include "threepp/loaders/AssimpLoader.hpp"
using namespace threepp;

class TankKeyControls: public KeyListener {

public:
    void onKeyPressed(KeyEvent) override;

};

#endif //TANK_KEYCONTROLLS_HPP


#endif //TANK_KEYCONTROLLS_HPP