#include "landscape2.hpp"

using namespace threepp;

landscape2::landscape2() {
    auto geometry  = PlaneGeometry::create(750,750);
    auto material = MeshPhongMaterial::create();
    material->color = Color(1.0f, 0.8f, 0.6f);

    groundMesh = Mesh::create(geometry, material);
    groundMesh->rotation.x = -math::PI / 2;
}

void landscape2::add_obstacle(threepp::Vector3 position) {
    auto geometry = BoxGeometry::create(5, 10, 5);
    auto material = MeshStandardMaterial::create({{"color", Color::purple}});

    auto obstacle = Mesh::create(geometry, material);
    obstacle->position.copy(position);
    obstacle->castShadow = true;
    objects.push_back(obstacle);
}
