#ifndef EXAM_TANK_HPP
#define EXAM_TANK_HPP

#pragma once
#include <threepp/threepp.hpp>
using namespace threepp;

class Tank: public threepp::Object3D {
public:
    std::shared_ptr<threepp::Mesh> mesh;

    Tank(const std::string& path) {
        threepp::STLLoader loader;
        auto geometry = loader.load(path);
        auto material = threepp::MeshStandardMaterial::create({{"color", threepp::Color::red}});
        mesh = threepp::Mesh::create(geometry, material);
        mesh->scale *= 0.001f;
    }
};

#endif //EXAM_TANK_HPP