#include "boost.hpp"
#include <cmath>

using namespace threepp;

power_up_boost::power_up_boost(Vector3 position) : initial_y_(position.y) {//From threepp examples/SphereGeometry
    auto geometry = SphereGeometry::create(2, 32, 32);

    //Found examepl on threepp clipping on how to use Meshpongmaterialet
    auto material = MeshPhongMaterial::create({{"color", Color::yellow},
    {"emissive", Color::orange},
    {"emissiveIntensity", 0.5f}}); //To make it glow a bit

    mesh_ = Mesh::create(geometry, material);
    mesh_->position.copy(position);
    mesh_->castShadow = true;

}

void power_up_boost::update(float dt){
    //So that the powerup moves up and down
    time_ += dt;
    mesh_->rotation.y += 2*dt;
    mesh_->position.y = initial_y_ - std::sin(time_)*1.5f;

}