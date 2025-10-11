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

    std::cout <<std::filesystem::current_path();

    //For kameraet
    PerspectiveCamera camera(60.0, canvas.aspect(), 0.1, 1000.0);
    camera.position.z = 15;
   // camera.lookAt({x:0, y:0, z:0}());

    //For å lage scenen
    auto scene = Scene::create();
    scene->background = Color::aliceblue;

    landscape land;
    std::shared_ptr<Mesh> groundMesh = land.groundMesh;
    scene->add(groundMesh);

    KeyListener listener;
    canvas.addKeyListener(listener);

    Clock clock;
    canvas.animate([&] {

        renderer.render(*scene, camera);
    });

    return 0;
}
