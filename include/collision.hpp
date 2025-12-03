#ifndef COLLISION_HPP
#define COLLISION_HPP
#include "threepp/threepp.hpp"


class collision {
public:
    static bool check_collision(threepp::Box3 tank_box, std::vector<std::shared_ptr<threepp::Group>> objects);

};

#endif //COLLISION_HPP