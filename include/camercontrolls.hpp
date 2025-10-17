#ifndef TANK_CAMERCONTROLLS_HPP
#define TANK_CAMERCONTROLLS_HPP
#include <threepp/threepp.hpp>

using namespace threepp;

class CameraFollow {
private:
    PerspectiveCamera& camera_;
    Object3D& target_;
    Vector3 offset_;
    float additionalRotation_ = 0.0f;  // Extra rotation in radians

public:
    // Constructor with default offset
    CameraFollow(PerspectiveCamera& camera, Object3D& target, Vector3 offset = Vector3(-20, 10, 0))
        : camera_(camera), target_(target), offset_(offset) {}

    void update() {
        // Create offset copy and rotate it with target
        Vector3 rotatedOffset = offset_;

        // Apply additional rotation if needed (e.g., 180 degrees = PI radians)
        if (additionalRotation_ != 0.0f) {
            Quaternion extraRotation;
            extraRotation.setFromAxisAngle(Vector3(0, 1, 0), additionalRotation_);
            rotatedOffset.applyQuaternion(extraRotation);
        }

        rotatedOffset.applyQuaternion(target_.quaternion);

        // Set camera position
        camera_.position.copy(target_.position);
        camera_.position.add(rotatedOffset);

        // Look at target
        camera_.lookAt(target_.position);
    }

    // Set the offset from the target (x, y, z relative to tank)
    void setOffset(const Vector3& offset) {
        offset_ = offset;
    }

    // Set offset using individual coordinates
    void setOffset(float x, float y, float z) {
        offset_.set(x, y, z);
    }

    // Add extra rotation (in radians). Use math::PI for 180 degrees
    void setAdditionalRotation(float radians) {
        additionalRotation_ = radians;
    }

    // Rotate 180 degrees around Y axis
    void rotate180() {
        additionalRotation_ = math::PI;
    }

    // Get current offset
    Vector3 getOffset() const {
        return offset_;
    }
};

#endif //TANK_CAMERCONTROLLS_HPP