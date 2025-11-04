#include "ammo.hpp"

using namespace threepp;

ammo::ammo(Vector3 position) : initla_y_(position.y){
    auto geometry = SphereGeometry::create(2, 32, 32);
    auto material = MeshPongMaterial::create({{"color", Color::Format::RGB(255,215, 0)}, //Ammog color - golden
    {"emissive", Color::yellow},
    {"emissiveInentsety", 0.5f}});


    mesh_ = Mesh::create(geometry, material);
    mesh_position_ = position;
    mesh_->castShadow = true;
}

void ammo::update(float dt){
    liftime_ += dt;
    mesh_->rotation.y += 2*dt;
    mesh_->position.y = initla_y_ + std::sin(time_)*0.5f;
}