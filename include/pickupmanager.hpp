#ifndef TANK_PICKUP_MANAGER_HPP
#define TANK_PICKUP_MANAGER_HPP

#include "threepp/threepp.hpp"
#include "boost.hpp"
#include "ammo.hpp"
#include <vector>
#include <memory>

class tank_attack;
class tank_movement;

class pickup_manager {
private:
    std::vector<std::unique_ptr<power_up_boost> > powerups_;
    std::vector<std::unique_ptr<ammo> > ammo_;

    static constexpr float pickup_collection_radius_ {5.0};

public:
    void spawn_powerups(threepp::Scene& scene, int count, float range_x, float range_z, float height);
    void spawn_ammo(threepp::Scene& scene, int count, float range_x, float range_z, float height);

    void update(float dt);

    void check_collisions(const threepp::Vector3 &tank_pos, tank_attack &attack, tank_movement &movement);

    void clear(threepp::Scene &scene);
};

#endif
