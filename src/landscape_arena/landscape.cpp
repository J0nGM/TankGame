#include "landscape.hpp"
#include "threepp/loaders/AssimpLoader.hpp"

using namespace threepp;


Landscape::Landscape() : Landscape(500.0f) {
}

//Creating the ground for the landscape
Landscape::Landscape(float ground_size) {
    groundGeometry = PlaneGeometry::create(ground_size, ground_size);
    groundMaterial = MeshStandardMaterial::create({{"color", Color::green}});
    groundMesh = Mesh::create(groundGeometry, groundMaterial);

    groundMesh->rotation.x = -math::PI / 2; //Rotates it so that it's flat on the ground
    groundMesh->position.y = 0;
    groundMesh->receiveShadow = true;

    //Creating a road in the landscape
    auto roadGeometry1 = PlaneGeometry::create(500, 20);
    auto roadMaterial1 = MeshStandardMaterial::create({{"color", Color::gray}});
    auto road1 = Mesh::create(roadGeometry1, roadMaterial1);
    road1->rotation.x = -math::PI / 2;
    road1->position.y = 0.01;
    road1->position.z = 0;
    roads.push_back(road1);

    //Road 2
    auto roadGeometry2 = PlaneGeometry::create(500, 20);
    auto roadMaterial2 = MeshStandardMaterial::create({{"color", Color::gray}});
    auto road2 = Mesh::create(roadGeometry2, roadMaterial2);
    road2->rotation.x = -math::PI / 2;
    road2->position.y = 0.01;
    road2->position.z = 100;
    roads.push_back(road2);
}

void Landscape::add_tree(threepp::Vector3 position) {
    auto tree = threepp::Group::create();

    auto tree_log_geometry = threepp::CylinderGeometry::create(tree_log_radius_, tree_log_radius_, tree_log_height_);
    auto tree_log_material = threepp::MeshStandardMaterial::create({{"color", threepp::Color::brown}});
    auto tree_log = threepp::Mesh::create(tree_log_geometry, tree_log_material);
    tree_log->position.y = tree_log_height_ * 0.5f;


    tree_log->castShadow = true;
    tree_log->receiveShadow = true;
    tree->add(tree_log);

    auto tree_cone_geometry = threepp::ConeGeometry::create(
        height_of_tree_ * cone_width_,
        height_of_tree_ * cone_height_,
        8
    );
    auto tree_cone_material = threepp::MeshStandardMaterial::create({{"color", threepp::Color::green}});
    auto tree_cone = threepp::Mesh::create(tree_cone_geometry, tree_cone_material);
    tree_cone->castShadow = true;
    tree_cone->receiveShadow = true;
    tree_cone->position.y = height_of_tree_ + (height_of_tree_ * cone_height_ * 0.6f); //Ender høyden på stammen
    tree->add(tree_cone);

    tree->position.copy(position);
    objects.push_back(tree);
}

void Landscape::spawn_trees(
    threepp::Scene &scene,
    std::function<threepp::Vector3(float, float, float)> random_position_func,
    float landscape_width,
    float landscape_depth) {
    float half_width = landscape_width / 2.0f;
    float half_depth = landscape_depth / 2.0f;

    for (int i = 0; i < amount_trees_spawned_; i++) {
        Vector3 pos = random_position_func(half_width, 0.0f, half_depth);

        //Safe zone around spawn
        if (std::abs(pos.x) < 40 && std::abs(pos.z) < 40) {
            continue;
        }

        add_tree(pos);
    }
}
