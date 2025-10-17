#ifndef TANK_CAMERCONTROLLS_HPP
#define TANK_CAMERCONTROLLS_HPP
#include <threepp/threepp.hpp>


class camera_Follow{
private:
    threepp::PerspectiveCamera& camera_;
    threepp::Object3D& target_;
    threepp::Vector3 offset_;
    float smoothSpeed_ = 0.1f;

public:
    camera_Follow(PerspectiveCamera& camera, Object3D& target, const Vector3& offset)
        : camera_(camera), target_(target), offset_(offset) {}
    void update(float dt) {
    Vector3 desired_position = target_.position + offset_;
        Vector3 rotated_offset = offset_;
        rotated_offset.applyQuaternion(target_.quaternion);
        desired_position = target_.position + rotated_offset;

        float lerp_factor = std::min(1.0f, dt / smoothSpeed_);
        camera_.position.lerp(desired_position, lerp_factor);
        camera_.lookAt(target_.position);
    }
    void set_delay(float seconds) {
        smoothSpeed_ = seconds;
    }
    void set_offset(const Vector3& offset) {
        offset_ = offset;
    }
};

#endif //TANK_CAMERCONTROLLS_HPP