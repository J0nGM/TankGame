#ifndef WINDOW_RESIZE_HPP
#define WINDOW_RESIZE_HPP

#include <threepp/threepp.hpp>

class window_resize_handler {
public:
    window_resize_handler(threepp::PerspectiveCamera &camera, threepp::GLRenderer &renderer);

    void operator()(const threepp::WindowSize &size);

private:
    threepp::PerspectiveCamera &camera_;
    threepp::GLRenderer &renderer_;
};

#endif WINDOW_RESIZE_HPP
