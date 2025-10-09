#include <iostream>
#include <threepp/threepp.hpp>

#include "threepp/materials/LineBasicMaterial.hpp"
//#include "cmake-build-debug/_deps/assimp-src/code/AssetLib/Blender/BlenderDNA.h"
#include "threepp/loaders/AssimpLoader.hpp"
#include "threepp/loaders/OBJLoader.hpp"

int main() {
    using namespace threepp;
    Canvas canvas;
    GLRenderer renderer(canvas.size());

    PerspectiveCamera camera(45, canvas.aspect(), 0.1, 10000);
    camera.position.set(0, 6, -10);

    OrbitControls controls{camera, canvas};

    auto ambientLight = AmbientLight::create(0xffffff, 0.5f);
    STLLoader loader;

    auto geometry = loader.load("../assets/Tank3.stl");
    auto material = MeshStandardMaterial::create({{"color", Color::red}});
    auto tank = Mesh::create(geometry, material);
    tank->scale *= 0.001;

    std::cout <<std::filesystem::current_path();

    //For kameraet
   // camera.lookAt({x:0, y:0, z:0}());

    //For å lage scenen
    auto scene = Scene::create();
    scene->background = Color::aliceblue;
    scene->add(tank);
    scene->add(ambientLight);


    KeyListener listener;
    canvas.addKeyListener(listener);

    Clock clock;
    canvas.animate([&] {

        renderer.render(*scene, camera);
    });

    return 0;
}
    //Loop for scenen
   /* canvas.animate([&] {
        camera.aspect = canvas.aspect();
        renderer.clear();
                renderer.render(*scene, camera);
            });
}*/
