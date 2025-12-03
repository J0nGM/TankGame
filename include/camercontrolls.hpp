#ifndef TANK_CAMERCONTROLLS_HPP
#define TANK_CAMERCONTROLLS_HPP

#include <threepp/threepp.hpp>
#include "keyinputhandler.hpp"

class Camera_follow {
private:
    threepp::PerspectiveCamera &camera_;
    threepp::Object3D &target_;
    key_input_handler &controls_;
    threepp::Vector3 base_offset_;
    const float smooth_speed_{0.1f};
    float min_distanse_{50.0f};
    float max_distanse_{80.0f};

public:
    Camera_follow(threepp::PerspectiveCamera &camera, threepp::Object3D &target,
                  key_input_handler &controls, const threepp::Vector3 &base_offset);

    void update(float dt);

    void set_delay(float seconds);

    void set_offset(const threepp::Vector3 &offset);

    void set_distance_range(float min_dist, float max_dist);
};

#endif
