#include "bullet.hpp"
#include <cmath>

using namespace threepp;

bullet::bullet(Vector3 position, Vector3 direction, float speed) {

    auto geomerty = SphereGeometry::create(0.5f, 8, 8);
    auto material = MeshPhongMaterial::create();
    material->color = Color::red;
    material->emissive = Color::orange;
    material->emissiveIntensity = 0.8f;

    mesh_ = Mesh::create(geomerty, material);
    mesh_->position.copy(position);
    mesh_->castShadow = true;

    velocity_ = direction;
    velocity_.normalize();
    velocity_.multiplyScalar(speed);
}

void bullet::update(float dt) {
    if (!active_) return;

    //Fikk hjelp av Ai for denn delen
    mesh_->position.addScaledVector(velocity_, dt); //Oppdaterer posisjonen basert på hastigheten og tidsdifferansen

    life_time_ += dt;
    if (life_time_ > max_life_time_) {
        deactivate();
    }
}
