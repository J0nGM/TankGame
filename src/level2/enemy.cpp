#include "enemy.hpp"

using namespace threepp;

enemy::enemy(threepp::Vector3 position) : position_(position) {
    auto body_geometry = CylinderGeometry::create(8,8,15);
    auto body_material = MeshStandardMaterial::create();
    body_material->color = Color::red;
    body_material->emissive = Color::darkred;
    body_material->emissiveIntensity = 0.5f;

    mesh_ = Mesh::create(body_geometry, body_material);
    mesh_->position.copy(position_);
    mesh_->castShadow = true;
}

void enemy::update(float dt) {
    if (is_destroyed) return;
    shoot_timer_ += dt;

    mesh_->rotation.y += 0.5f * dt;
}

bool enemy::should_shoot() {
    if (is_destroyed) return false;
    if (shoot_timer_ >= shoot_intreval_) {
        shoot_timer_ = 0.0f;
        return true;
    }
    return false;
}

void enemy::take_damage() {
    if (is_destroyed) {
        return;
    }
    hp_--;
    if (hp_ <= 0) {
        is_destroyed = true;
        mesh_->visible = false;
    }
}


