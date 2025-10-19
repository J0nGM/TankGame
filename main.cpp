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
    auto geometry = loader.load("../assets/Tank4.glb");
    geometry->traverseType<Mesh>([](Mesh& m) {
        m.receiveShadow = true;
        m.castShadow = true;
    });
    geometry->scale *= 1000;
    //Kameret
    PerspectiveCamera camera(45, canvas.aspect(), 0.1, 10000);
    camera.position.set(0, 6, -10);
    OrbitControls controls{camera, canvas};




    auto scene = Scene::create();
    scene->background = Color::aliceblue;


    //Legger til lys
    auto light = HemisphereLight::create(0xffffbb, 0x080820);
    scene->add(light);

    // After loading geometry
    scene->add(geometry);
    geometry->position = {0, 10, 0};


    landscape land;
    std::shared_ptr<Mesh> groundMesh = land.groundMesh;
    groundMesh ->receiveShadow = true;
    scene->add(groundMesh);

    //Har ikke gjort noe med dette ennå
    KeyListener listener;
    canvas.addKeyListener(listener);

    Clock clock;
    canvas.animate([&] {

        renderer.render(*scene, camera);
    });

    return 0;
}
