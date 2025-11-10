#ifndef TANK_LANDSCAPE2_HPP
#define TANK_LANDSCAPE2_HPP

#include <iostream>
#include <threepp/threepp.hpp>
class landscape2 {
public:
    std::shared_ptr<threepp::Mesh> groundMesh;
    std::vector<std::shared_ptr<threepp::Object3D>> objects;
    std::vector<std::shared_ptr<threepp::Mesh>> roads;

    landscape2();
    void add_obstacle(threepp::Vector3 position);
};

#endif //TANK_LANDSCAPE2_HPP