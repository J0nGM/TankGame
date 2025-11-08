#include <iostream>
#include <threepp/threepp.hpp>
#include "tank.hpp"
#include "keycontrolls.hpp"
#include "landscape.hpp"
#include "WindowResize.hpp"
#include "camercontrolls.hpp"
#include <cmath>
#include "gamemanger/gamemanger.hpp"

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

    /* Box3 bb;
     bb.setFromObject(tank);*/

    Key_controlls key_controls(tank);
    canvas.addKeyListener(key_controls);
    std::cout << "Use WASD keys to steer tank, Press 'r' to reset tank position." << std::endl;


    Camera_follow camera_follow(camera, tank, key_controls, Vector3(60, 20, 0));

    Landscape land;
    auto ground_mesh = land.groundMesh;
    ground_mesh->position.y = -0.5f;
    ground_mesh->receiveShadow = true;
    scene->add(ground_mesh);
    for (const auto &road: land.roads) {
        scene->add(road);
    }

    //Lagern en for løkke som generere trær helt randomt på landskapet
    int num_trees{1};
    //Hjelp fra AI for å generere random trær
    for (int i = 0; i < num_trees; i++) {
        float random_x = (rand() % 500) - 250;
        float random_z = (rand() % 500) - 250;
        land.add_tree(Vector3(random_x, 0, random_z));
    }

    for (const auto &tree: land.objects) {
        scene->add(tree);
    }

    game_manger game(*scene, tank, key_controls, land, camera_follow);
    game.setup_powerups(8); //Ammount of boosts I can pickup in the game
    game.setup_ammo(8); //Ammount ammo you get for when picked up

    Clock clock;
    canvas.animate([&] {
        float dt = clock.getDelta();
        game.update(dt);
        renderer.render(*scene, camera);
    });

    return 0;
}
