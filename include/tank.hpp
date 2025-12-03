#pragma once //endre denne ettervert

#include <threepp/threepp.hpp>
#include "threepp/loaders/AssimpLoader.hpp"

class tank : public threepp::Object3D {
public:
    std::shared_ptr<threepp::Mesh> mesh = threepp::Mesh::create();

    tank(const std::string &path, threepp::Scene& scene);
};

