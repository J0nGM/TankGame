#ifndef TANK_CAMERA_HPP
#define TANK_CAMERA_HPP

#include <threepp/threepp.hpp>

class window_resize_handler {
public:
    window_resize_handler(threepp::PerspectiveCamera &camera, threepp::GLRenderer &renderer);

    void operator()(const threepp::WindowSize &size);

private:
    threepp::PerspectiveCamera &camera_;
    threepp::GLRenderer &renderer_;
};

#endif //TANK_CAMERA_HPP
