//
// Created by L14 G5 on 10/11/2025.
//

#ifndef TANK_LANDSCAPE_HPP
#define TANK_LANDSCAPE_HPP
#include <iostream>
#include <threepp/threepp.hpp>


class Landscape {
private:
    //For å endre på trærene
    const float height_tree_ {10.0f};
    const float tree_log_radius_ {2.0f};
    const float tree_log_height_ {15.0f};
    const float cone_width_ {1.5f};
    const float cone_height_ {3.0f};

public:
    std::shared_ptr<threepp::PlaneGeometry>groundGeometry = threepp::PlaneGeometry::create(500, 500);
    std::shared_ptr<threepp::MeshStandardMaterial>groundMaterial = threepp::MeshStandardMaterial::create({{"color", threepp::Color::green}});
    std::shared_ptr<threepp::Mesh>groundMesh = threepp::Mesh::create(groundGeometry, groundMaterial);
    std::vector<std::shared_ptr<threepp::Group>> objects;

    std::vector<std::shared_ptr<threepp::Mesh>> roads;

    Landscape();
    void add_tree(threepp::Vector3 position);
};
#endif //TANK_lANDSCAPE_HPP