#include "landscape.hpp"
#include "threepp/loaders/AssimpLoader.hpp"

using namespace threepp;

//Slik at jeg kan endre høyden på træerene. Kansje rydde opp i den funksjonen seinre.
Landscape::Landscape() {
    groundMesh->rotation.x = -math::PI / 2; //Gjør slik at bakken blir helt flat
    groundMesh->position.y = 0;

    //Lager vei, for landskapet
    auto roadGeometry1 = PlaneGeometry::create(500, 20);
    auto roadMaterial1 = MeshStandardMaterial::create({{"color", Color::gray}});
    auto road1 = Mesh::create(roadGeometry1, roadMaterial1);
    road1->rotation.x = -math::PI / 2;
    road1->position.y = 0.01;
    road1->position.z = 0;
    roads.push_back(road1);

    //Vei 2
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

        auto tree_log_geometry = threepp::CylinderGeometry::create(tree_log_radius, tree_log_radius, tree_log_height);
        auto tree_log_material = threepp::MeshStandardMaterial::create({{"color", threepp::Color::brown}});
        auto tree_log = threepp::Mesh::create(tree_log_geometry, tree_log_material);
        tree_log->position.y= tree_log_height *0.5f;


        tree_log->castShadow = true;
        tree_log->receiveShadow = true;
        tree->add(tree_log);

        auto tree_cone_geometry = threepp::ConeGeometry::create(
            height_tree * cone_width,
            height_tree * cone_height,
            8
            );
        auto tree_cone_material = threepp::MeshStandardMaterial::create({{"color", threepp::Color::green}});
        auto tree_cone = threepp::Mesh::create(tree_cone_geometry, tree_cone_material);
        tree_cone->castShadow = true;
        tree_cone->receiveShadow = true;
        tree_cone->position.y = height_tree + (height_tree * cone_height * 0.6f); //Ender høyden på stammen
        tree->add(tree_cone);

        tree->position.copy(position);
        objects.push_back(tree);
}