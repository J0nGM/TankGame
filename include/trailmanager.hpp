#ifndef TANK_TRAILMANGER_HPP
#define TANK_TRAILMANGER_HPP
#include "trail.hpp"

class trail_manager {
public:
    trail_manager(threepp::Scene* scene);

    void add_trail(const threepp::Vector3& position, const threepp::Vector3& right_direction);
    void update(float dt);
    void clear();

private:
    threepp::Scene* scene_;
    std::vector<trail> segments_;
};




#endif //TANK_TRAILMANGER_HPP