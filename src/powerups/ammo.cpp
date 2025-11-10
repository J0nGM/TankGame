#include "ammo.hpp"
#include <cmath>
#include <iostream>

using namespace threepp;

ammo::ammo(Vector3 position) : initla_y_(position.y){
    auto geometry = SphereGeometry::create(2, 32, 32);

    //From threepp clipping example
    auto material = MeshPhongMaterial::create({
        {"color", Color(0, 1, 0.0f)}, //Ammog color green
    {"emissive", Color::green},
    {"emissiveInentsety", 0.5f}});


    mesh_ = Mesh::create(geometry, material);
    mesh_->position.copy(position);
    mesh_->castShadow = true;
}

void ammo::update(float dt){
    lifetime_ += dt;
    mesh_->rotation.y += 2*dt;
    mesh_->position.y = initla_y_ + std::sin(lifetime_)*1.5f;
}