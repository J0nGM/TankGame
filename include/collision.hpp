//
// Created by L14 G5 on 10/28/2025.
//

#ifndef TANK_COLLISION_HPP
#define TANK_COLLISION_HPP
#include "threepp/threepp.hpp"


class collision {
public: //Velger å bruke bool, fordi jeg må bare ha true eller false feedback på om det er kollisjon eller ikke
    static bool check_collision(threepp::Box3 tank_box, std::vector<std::shared_ptr<threepp::Group>> objects);

};

#endif //TANK_COLLISION_HPP