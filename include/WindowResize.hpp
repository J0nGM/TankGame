
#ifndef TANK_CAMERA_HPP
#define TANK_CAMERA_HPP

#include <threepp/threepp.hpp>
using namespace threepp;

// C++
class WindowResizeHandler {

    public:
    WindowResizeHandler(PerspectiveCamera& camera, GLRenderer& renderer)
        : camera_(camera), renderer_(renderer) {}

    void operator()(const threepp::WindowSize& size) {
        camera_.aspect = size.aspect();
        camera_.updateProjectionMatrix();
        renderer_.setSize(size);
    }

private:
    PerspectiveCamera& camera_;
    GLRenderer& renderer_;
};

#endif //TANK_CAMERA_HPP