#include "tank.hpp"


#include "threepp/threepp.hpp"
using namespace threepp;

float scale_tank {15.0f}; //endre på størreslen til tanksen her
float degrees {180.0f};

Tank::Tank(const std::string &path) {
    threepp::AssimpLoader loader;
    auto loadedGroup = loader.load(path);

    loadedGroup->traverseType<threepp::Mesh>([](threepp::Mesh &m) {
        m.receiveShadow = true;
        m.castShadow = true;
    });
    loadedGroup->scale.set(scale_tank, scale_tank, scale_tank);
    loadedGroup->rotateY(threepp::math::degToRad(degrees)); //Rotere tanksen 180 grader, for at W/S går riktig vei


    add(loadedGroup);
}
