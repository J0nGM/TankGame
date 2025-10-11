//
// Created by L14 G5 on 10/11/2025.
//

#ifndef TANK_LANDSCAPE_HPP
#define TANK_LANDSCAPE_HPP
#include <iostream>
#include <threepp/threepp.hpp>

using namespace threepp;

class landscape {
public:
    std::shared_ptr<PlaneGeometry>groundGeometry = PlaneGeometry::create(1000, 1000);
    std::shared_ptr<MeshStandardMaterial>groundMaterial = MeshStandardMaterial::create({{"color", Color::green}});
    std::shared_ptr<Mesh>groundMesh = Mesh::create(groundGeometry, groundMaterial);

    landscape() {
        groundMesh->rotation.x = -math::PI / 2; //Gjør slik at bakken blir helt flat
        groundMesh->position.y = 0;
    }
};
#endif //TANK_lANDSCAPE_HPP