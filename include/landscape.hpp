#ifndef TANK_LANDSCAPE_HPP
#define TANK_LANDSCAPE_HPP
#include <iostream>
#include <threepp/threepp.hpp>


class Landscape {
protected:
    //To cahnge the size of the trees
    const float height_of_tree_ {10.0f};
    const float tree_log_radius_ {2.0f};
    const float tree_log_height_ {15.0f};
    const float cone_width_ {1.5f};
    const float cone_height_ {3.0f};
    const int amount_trees_spawned_{1};

    const int ground_width_{500};
    const int ground_heigth_{500};

public:
    std::shared_ptr<threepp::PlaneGeometry>groundGeometry = threepp::PlaneGeometry::create(ground_width_, ground_heigth_);
    std::shared_ptr<threepp::MeshStandardMaterial>groundMaterial = threepp::MeshStandardMaterial::create({{"color", threepp::Color::green}});
    std::shared_ptr<threepp::Mesh>groundMesh = threepp::Mesh::create(groundGeometry, groundMaterial);
    std::vector<std::shared_ptr<threepp::Group>> objects;

    std::vector<std::shared_ptr<threepp::Mesh>> roads;

    //This is so that landscape 2 can inherit from landscape 1. Got som ai help
    Landscape();
    Landscape(float ground_size);
    virtual ~Landscape() = default; //for arv
    void add_tree(threepp::Vector3 position);

    void spawn_trees(
    threepp::Scene& scene,
    std::function<threepp::Vector3(float, float, float)> random_position_func,
    float landscape_width,
    float landscape_depth);
};
#endif //TANK_lANDSCAPE_HPP