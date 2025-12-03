#include "portalLVL2.hpp"

using namespace threepp;

portal_lvl2::portal_lvl2(Vector3 position) {
    auto geometry = BoxGeometry::create(7, 20, 1);
    auto material = MeshStandardMaterial::create({
        {"color", Color::purple},
        {"emissive", Color::purple},
        {"emissiveIntensity", 0.8f}
    });

    mesh_ = Mesh::create(geometry, material);
    mesh_->position.copy(position);
    mesh_->castShadow = true;
}

void portal_lvl2::update(float dt) {
    time_ += dt;
    mesh_->rotation.y += 1.0f * dt;

    //flaot pulse = 0.5f + 0.3f * std::sin(time_*0.3f); maybe add this later (pulsing effect)
}