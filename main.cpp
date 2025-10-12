#include <iostream>
#include <threepp/threepp.hpp>
#include "tank.hpp"
#include "threepp/materials/LineBasicMaterial.hpp"
//#include "cmake-build-debug/_deps/assimp-src/code/AssetLib/Blender/BlenderDNA.h"
#include "keycontrolls.hpp"
#include "landscape.hpp"
#include "threepp/loaders/AssimpLoader.hpp"
#include "threepp/loaders/OBJLoader.hpp"
#include "threepp/helpers/CameraHelper.hpp"


int main() {
    using namespace threepp;
    Canvas canvas;
    GLRenderer renderer(canvas.size());

    PerspectiveCamera camera(45, canvas.aspect(), 0.1, 10000);
    camera.position.set(0, 6, -10);
    OrbitControls controls{camera, canvas};



    //Legger til lys
    auto light = HemisphereLight::create(0xffffbb, 0x080820);

    std::cout << std::filesystem::current_path();

    //For å lage scenen
    auto scene = Scene::create();
    scene->background = Color::aliceblue;
    scene->add(light);


    //Legger til tanksen i scenen
    Tank tank("../assets/Tank3.stl");
    scene->add(tank.mesh);

    /*auto &tankCamera = tank.camera();
    auto cameraHelper = CameraHelper::create(tankCamera);
    scene->add(cameraHelper);*/

    //Landskap for at tanksen kan kjøre rundt
    landscape land;
    auto groundMesh = land.groundMesh;
    groundMesh->position.y = -0.5f;
    groundMesh->receiveShadow = true;
    scene->add(groundMesh);


    //Object3D obj;
    keycontrolls keyControls(*tank.mesh); // Pass the tank's mesh
    canvas.addKeyListener(keyControls);
    std::cout << "Press 'r' to reset tank position. Use WASD keys to steer tank" << std::endl;

    Clock clock;
    canvas.animate([&] {
        double dt = clock.getDelta();
        keyControls.update(dt); //For å knappen av bevegsel til å oppdatere seg
        renderer.render(*scene, camera);
    });

    return 0;
}
