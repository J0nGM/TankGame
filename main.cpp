#include <iostream>
#include <threepp/threepp.hpp>

//#include "cmake-build-debug/_deps/assimp-src/code/AssetLib/Blender/BlenderDNA.h"
#include "landscape.hpp"
#include "threepp/loaders/AssimpLoader.hpp"

int main() {
    using namespace threepp;
    Canvas canvas;
    GLRenderer renderer(canvas.size());

    AssimpLoader loader;
   // auto geometry = loader.load("Tank.glb");

    auto ambientLight = AmbientLight::create(0xffffff, 0.5f);


    std::cout <<std::filesystem::current_path();

    //For kameraet
    PerspectiveCamera camera(45, canvas.aspect(), 0.1, 10000);
    camera.position.set(0, 6, -10);
    OrbitControls controls{camera, canvas};
   // camera.lookAt({x:0, y:0, z:0}());

    //For å lage scenen
    auto scene = Scene::create();
    scene->background = Color::aliceblue;

    //Legger til lys
    auto light = HemisphereLight::create(0xffffbb, 0x080820);
    scene->add(light);


    landscape land;
    std::shared_ptr<Mesh> groundMesh = land.groundMesh;
    groundMesh ->receiveShadow = true;
    scene->add(groundMesh);

    KeyListener listener;
    canvas.addKeyListener(listener);

    Clock clock;
    canvas.animate([&] {

        renderer.render(*scene, camera);
    });

    return 0;
}
