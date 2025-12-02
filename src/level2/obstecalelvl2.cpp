#include "obstecalelvl2.hpp"

using namespace threepp;

obsticale_lvl2::obsticale_lvl2(const Vector3& position, obsticale_type_lvl_2 type)
: position_(position), type_(type) {

    //creatinh the barrieres
        auto geometry = BoxGeometry::create(20, 5, 4);
        auto material = MeshPhongMaterial::create(
            {{"color", Color::brown},
                {"emissive", Color::brown},
                {"emissiveIntensity", 0.3f}});

        mesh_ = Mesh::create(geometry, material);


    mesh_->position.copy(position_);
    mesh_->castShadow = true;
    mesh_->receiveShadow = true;
}

void obstacle_manger_lvl2::add_obstical(const Vector3& position, obsticale_type_lvl_2 type) {
    obsticale_lvl2_.push_back(std::make_unique<obsticale_lvl2>(position, type));
}

//Ai helped me with this function. So that I can add barriers easier
void obstacle_manger_lvl2::spawn_barriers_randomly(Scene& scene,
    std::function<Vector3(float, float, float)> random_position_func) {

    constexpr int number_barriers = 50;

    for (int i = 0; i < number_barriers; i++) {
        Vector3 pos = random_position_func(700.0f, 2.5f, 700.0f);

        if (std::abs(pos.x) < 40 && std::abs(pos.z) < 40) {
            continue;
        }

        add_obstical(pos, obsticale_type_lvl_2::BARRIER);
    }
}

void obstacle_manger_lvl2::add_to_scene(threepp::Scene &scene) {
    for (auto& obstacle : obsticale_lvl2_) {
        scene.add(obstacle->get_mesh());
    }
}

void obstacle_manger_lvl2::clear_obstacles(threepp::Scene &scene) {
    for (auto& obstacle : obsticale_lvl2_) {
        scene.remove(*obstacle->get_mesh());
    }
    obsticale_lvl2_.clear();
}

