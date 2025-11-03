#include "boost.hpp"
#include <cmath>

using namespace threepp;

power_up_boost::power_up_boost(Vector3 position) : initial_y_(position.y) {
    auto geometry = SphereGeometry::create(2, 32, 32);

    //Tatt fra threepp clipping eksempel for å lage Meshpongmaterialet
    auto material = MeshPhongMaterial::create({{"color", Color::yellow},
    {"emissive", Color::orange},
    {"emissiveInentsety", 0.5f}}); //For å gjør powerupen gul med gjenskinn

        mesh_ = Mesh::create(geometry, material);
        mesh_->position.copy(position);
        mesh_->castShadow = true;

}

void power_up_boost::update(float dt){
    time_ += dt;
    //Slik at powerupen beveger seg opp og ned
     //fikk help av AI for å få den til å bevege seg opp og ned
    mesh_->rotation.y += 2*dt;
    mesh_->position.y = initial_y_ + std::sin(time_)*0.5f;

}