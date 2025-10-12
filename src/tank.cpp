#include "tank.hpp"

#include "threepp/helpers/CameraHelper.hpp"
#include "threepp/threepp.hpp"
using namespace threepp;

// In your class or function
void addCameraHelperToScene(Scene& scene, PerspectiveCamera& camera) {
    auto cameraHelper = CameraHelper::create(camera);
    scene.add(cameraHelper);
}
