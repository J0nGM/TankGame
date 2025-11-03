#include "camercontrolls.hpp"

Camera_follow::Camera_follow(PerspectiveCamera &camera, Object3D &target, Key_controlls &controls,
                             const Vector3 &base_offset) : camera_(camera), target_(target), controls_(controls),
                                                           base_offset_(base_offset) {
}

void Camera_follow::update(float dt) {
    double dynamic_distance = base_offset_.x;

    if (controls_.get_direction_moved() == 1) {
        float speed = controls_.get_speed();
        double speed_rotation = speed / 20.0f;
        dynamic_distance = min_distanse_ + speed_rotation * (max_distanse_ - min_distanse_);
    };

    threepp::Vector3 offset = base_offset_;
    offset.x = dynamic_distance;


    threepp::Vector3 rotated_offset = offset;
    rotated_offset.applyQuaternion(target_.quaternion);
    threepp::Vector3 desired_position = target_.position + rotated_offset;

    float lerp_factor = std::min(1.0f, dt / smoothSpeed_);
    camera_.position.lerp(desired_position, lerp_factor);
    camera_.lookAt(target_.position);
}

void Camera_follow::set_delay(float seconds) {
    smoothSpeed_ = seconds;
}

void Camera_follow::set_offset(const Vector3 &offset) {
    base_offset_ = offset;
}

void Camera_follow::set_distance_range(float min_dist, float max_dist) {
    min_distanse_ = min_dist;
    max_distanse_ = max_dist;
}
