#include "WindowResize.hpp"

using namespace threepp;

Window_resize_handler::Window_resize_handler(threepp::PerspectiveCamera &camera,
                                             threepp::GLRenderer &renderer) : camera_(camera), renderer_(renderer) {
}

void Window_resize_handler::operator()(const threepp::WindowSize &size) {
    camera_.aspect = size.aspect();
    camera_.updateProjectionMatrix();
    renderer_.setSize(size);
}
