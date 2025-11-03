#ifndef TANK_CAMERCONTROLLS_HPP
#define TANK_CAMERCONTROLLS_HPP
#include <threepp/threepp.hpp>
#include "keycontrolls.hpp"

class Camera_follow {
private:
    threepp::PerspectiveCamera &camera_;
    threepp::Object3D &target_;
    Key_controlls &controls_;
    threepp::Vector3 base_offset_;
    float smoothSpeed_ = 0.1f;
    float min_distanse_ = 50.0f; //hvor nærme kameraet zoomer når man akselerer
    float max_distanse_ = 70.0f;


    //Fikk hjelp av AI å lage denne delen her
public:
    Camera_follow(PerspectiveCamera &camera, Object3D &target, Key_controlls &controls, const Vector3 &base_offset);


    void update(float dt);

    void set_delay(float seconds);

    void set_offset(const Vector3 &offset);

    void set_distance_range(float min_dist, float max_dist);
};

#endif //TANK_CAMERCONTROLLS_HPP
