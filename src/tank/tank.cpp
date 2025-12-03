#include "tank.hpp"


#include "threepp/threepp.hpp"
using namespace threepp;

float scale_tank {15.0};
float degrees {180.0};

tank::tank(const std::string &path, threepp::Scene& scene) {
    threepp::AssimpLoader loader;
    auto loadedGroup = loader.load(path);

    loadedGroup->traverseType<threepp::Mesh>([](threepp::Mesh &m) {
        m.receiveShadow = true;
        m.castShadow = true;
    });
    loadedGroup->scale.set(scale_tank, scale_tank, scale_tank);
    loadedGroup->rotateY(threepp::math::degToRad(degrees)); //Rotated the tank 180 degrees, so that W/S-buttons where correct way


    add(loadedGroup);
    this->position.y = 5.0;
    scene.add(*this);
}
