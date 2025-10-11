#include <iostream>
#include <threepp/threepp.hpp>
#include "tank.hpp"
#include "threepp/materials/LineBasicMaterial.hpp"
//#include "cmake-build-debug/_deps/assimp-src/code/AssetLib/Blender/BlenderDNA.h"
#include "landscape.hpp"
#include "threepp/loaders/AssimpLoader.hpp"
#include "threepp/loaders/OBJLoader.hpp"

int main() {
    using namespace threepp;
    Canvas canvas;
    GLRenderer renderer(canvas.size());

    PerspectiveCamera camera(45, canvas.aspect(), 0.1, 10000);
    camera.position.set(0, 6, -10);
    OrbitControls controls{camera, canvas};

    //Laster inn STL filen
    auto ambientLight = AmbientLight::create(0xffffff, 0.5f);
    STLLoader loader;


    std::cout << std::filesystem::current_path();

    //For å lage scenen
    auto scene = Scene::create();
    scene->background = Color::aliceblue;


    //Legger til tanksen i scenen
    Tank tank("../assets/Tank3.stl");
    scene->add(tank.mesh);
    scene->add(ambientLight);


    //Landskap for at tanksen kan kjøre rundt
    landscape land;
    auto groundMesh = land.groundMesh;
    groundMesh->position.y = -0.5f;
    groundMesh->receiveShadow = true;
    scene->add(groundMesh);


    KeyListener listener;
    canvas.addKeyListener(listener);

    Clock clock;
    canvas.animate([&] {
        renderer.render(*scene, camera);
    });

    return 0;
}
