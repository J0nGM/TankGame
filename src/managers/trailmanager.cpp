#include "trailmanager.hpp"
#include <iostream>

using namespace threepp;

trail_manager::trail_manager(threepp::Scene *scene) : scene_(scene) {
}

void trail_manager::add_trail(const threepp::Vector3 &position, const threepp::Vector3 &right_direction) {
    const float track_offset_left = 6.0f;
    const float track_offsett_right = 5.0f;

    //This is for the creation of the trails left by the tank. So it seems like its moving

    //Left trail
    auto geometry_left = threepp::BoxGeometry::create(1.0f, 0.02f, 1.8f);
    auto material_left = threepp::MeshBasicMaterial::create();
    material_left->color.setHex(0x333333); //Gray color
    material_left->transparent = true;

    auto mesh_left = Mesh::create(geometry_left, material_left);
    mesh_left->position.copy(position);
    mesh_left->position.y = 0.05f; //to take it a little above the ground

    //Use the right direction to offset, Hade issues with this got a little help from AI to solve this issue
    Vector3 left_offset = right_direction;
    left_offset.multiplyScalar(-track_offset_left);
    mesh_left->position.add(left_offset);

    scene_->add(mesh_left);
    trail trail_left(mesh_left);
    segments_.push_back(trail_left);


    //Right trail
    auto geometry_right = threepp::BoxGeometry::create(1.0f, 0.02f, 1.8f);
    auto material_right = threepp::MeshBasicMaterial::create();
    material_right->color.setHex(0x333333); //Grey color
    material_right->transparent = true;

    auto mesh_right = Mesh::create(geometry_right, material_right);
    mesh_right->position.copy(position);
    mesh_right->position.y = 0.05f;

    //Use the right direction to offset, Hade issues with this got a little help from AI to solve this issue
    Vector3 right_offset = right_direction;
    right_offset.multiplyScalar(track_offsett_right);
    mesh_right->position.add(right_offset);

    scene_->add(mesh_right);
    trail trail_right(mesh_right);
    segments_.push_back(trail_right);
}

void trail_manager::update(float dt) {
    //Got AI assistance here
    for (auto it = segments_.begin(); it != segments_.end();) {
        it->life_time -= dt;

        if (it->life_time <= 0.0f) {
            scene_->remove(*it->mesh);
            it = segments_.erase(it);
        } else {
            //THe faid of the trail after it has been created
            float alpha = it->life_time / it->max_lifetime_;


            auto material = std::dynamic_pointer_cast<threepp::MeshBasicMaterial>(it->mesh->material());
            if (material) {
                material->opacity = alpha;
            }

            ++it;
        }
    }
}
