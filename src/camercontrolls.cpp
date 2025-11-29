#include "camercontrolls.hpp"

using namespace threepp;

Camera_follow::Camera_follow(PerspectiveCamera &camera, Object3D &target,
                             key_input_handler &controls,
                             const Vector3 &base_offset)
    : camera_(camera),
      target_(target),
      controls_(controls),
      base_offset_(base_offset) {
}

void Camera_follow::update(float dt) {
    const auto& keys = controls_.get_keys();

    float dynamic_distance = base_offset_.x;

    // Adjust camera distance based on movement
    if (keys.up || keys.down) {
        dynamic_distance = (keys.up) ? max_distanse_ : min_distanse_;
    }

    Vector3 offset = base_offset_;
    offset.x = dynamic_distance;

    Vector3 rotated_offset = offset;
    rotated_offset.applyQuaternion(target_.quaternion);

    Vector3 desired_position = target_.position;
    desired_position.add(rotated_offset);

    camera_.position.lerp(desired_position, smooth_speed_);
    camera_.lookAt(target_.position);
}

void Camera_follow::set_delay(float seconds) {
    // Implementation for delay if needed
}

void Camera_follow::set_offset(const Vector3 &offset) {
    base_offset_ = offset;
}

void Camera_follow::set_distance_range(float min_dist, float max_dist) {
    min_distanse_ = min_dist;
    max_distanse_ = max_dist;
}
