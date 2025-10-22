#include <iostream>
#include <threepp/threepp.hpp>
#include "tank.hpp"
#include "threepp/materials/LineBasicMaterial.hpp"
#include "keycontrolls.hpp"
#include "landscape.hpp"
#include "WindowResize.hpp"
#include "camercontrolls.hpp"

int main() {
    using namespace threepp;
    Canvas canvas;
    GLRenderer renderer(canvas.size());

    PerspectiveCamera camera(45, canvas.aspect(), 0.1, 10000);
    camera.position.set(0, 50, 100);


    Window_resize_handler resizeHandler(camera, renderer);
    canvas.onWindowResize(resizeHandler);


    auto light = HemisphereLight::create(0xffffbb, 0x080820);

    std::cout << std::filesystem::current_path();


    auto scene = Scene::create();
    scene->background = Color::aliceblue;
    scene->add(light);



    Tank tank("../assets/3Dmodell/viecal/Tank.glb");

    tank.position.y = 5.0f;
    scene->add(tank);

    Box3 bb;

    bb.setFromObject(tank);


    Key_controlls key_controls(tank);
    canvas.addKeyListener(key_controls);
    std::cout << "Press 'r' to reset tank position. Use WASD keys to steer tank" << std::endl;


    Camera_follow camera_follow(camera, tank, key_controls, Vector3(60, 20, 0));

    Landscape land;
    auto ground_mesh = land.groundMesh;
    ground_mesh->position.y = -0.5f;
    ground_mesh->receiveShadow = true;
    scene->add(ground_mesh);
    for (const auto &road: land.roads) {
        scene->add(road);
    }

    for (int x = -200; x <= 200; x+=200) {
        for (int z = -200; z <= 200; z += 200) {
            land.add_tree(Vector3(x, 0, z));
        }
    }

    for (const auto &tree : land.objects) {
        scene->add(tree);
    }


    Clock clock;
    canvas.animate([&] {
        double dt = clock.getDelta();
        key_controls.update(dt);
        camera_follow.update(static_cast<float>(dt));

        renderer.render(*scene, camera);
    });

    return 0;
}