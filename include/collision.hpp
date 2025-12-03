//
// Created by L14 G5 on 10/28/2025.
//

#ifndef TANK_COLLISION_HPP
#define TANK_COLLISION_HPP
#include "threepp/threepp.hpp"


class collision {
public:
    static bool check_collision(threepp::Box3 tank_box, std::vector<std::shared_ptr<threepp::Group>> objects);

};

#endif //TANK_COLLISION_HPP