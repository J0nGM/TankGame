#include "enemy.hpp"

using namespace threepp;

Enemy::Enemy(threepp::Vector3 position) : position_(position) {
    auto body_geometry = CylinderGeometry::create(3,3,5);
    auto body_material = MeshStandardMaterial::create();
    body_material->color = Color::red;

    mesh_ = Mesh::create(body_geometry, body_material);
    mesh_->position.copy(position_);
    mesh_->castShadow = true;
}

void Enemy::update(float dt) {
    if (is_destryd) return;
    shoot_timer_ += dt;
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
    hp_--;
    if (hp_ <= 0) {
        is_destryd = true;
        mesh_->visible = false;
    }
}


