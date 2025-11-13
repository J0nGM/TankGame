#include "enemy.hpp"

using namespace threepp;

Enemy::Enemy(threepp::Vector3 position) : position_(position) {
    auto body_geometry = CylinderGeometry::create(8,8,25);
    auto body_material = MeshStandardMaterial::create();
    body_material->color = Color::red;
    body_material->emissive = Color::darkred;
    body_material->emissiveIntensity = 0.5f;

    mesh_ = Mesh::create(body_geometry, body_material);
    mesh_->position.copy(position_);
    mesh_->castShadow = true;
}

void Enemy::update(float dt) {
    if (is_destryd) return;
    shoot_timer_ += dt;

    mesh_->rotation.y += 0.5f * dt;
}

bool Enemy::should_shoot() {
    if (is_destryd) return false;
    if (shoot_timer_ >= shoot_intreval_) {
        shoot_timer_ = 0.0f;
        return true;
    }
    return false;
}

void Enemy::take_damage() {
    if (is_destryd) {
    return;
}
    hp_--;
    if (hp_ <= 0) {
        is_destryd = true;
        mesh_->visible = false;
    }
}


