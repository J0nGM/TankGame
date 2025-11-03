#include <iostream>
#include <threepp/threepp.hpp>
#include "tank.hpp"
#include "threepp/materials/LineBasicMaterial.hpp"
#include "keycontrolls.hpp"
#include "landscape.hpp"
#include "WindowResize.hpp"
#include "camercontrolls.hpp"
#include <random>
#include <cmath>
#include "collision.hpp"
#include "boost.hpp"

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
    std::vector<std::unique_ptr<power_up_boost>> powerups;
    //Lagern en for løkke som generere trær helt randomt på landskapet
    int num_trees{20};
    //Hjelp fra AI for å generere random trær
    for (int i = 0; i < num_trees; i++) {
        float random_x = (rand() % 500) - 250;
        float random_z = (rand() % 500) - 250;
        land.add_tree(Vector3(random_x, 0, random_z));


    }

    for (const auto &tree: land.objects) {
        scene->add(tree);
    }
    //Plasserer ut powerups randomt på kartet
    int num_powerups{8};
    for (int i = 0; i < num_powerups; i++) {
        float random_x = (rand() % 400) - 200;
        float random_z = (rand() % 400) - 200;

        auto powerup_boost = std::make_unique<power_up_boost>(Vector3(random_x, 3.0f, random_z));
        scene->add(powerup_boost->getMesh());
        powerups.push_back(std::move(powerup_boost));

    }

    Clock clock;
    canvas.animate([&] {
        float dt = clock.getDelta();
        Vector3 old_position = tank.position;
        key_controls.update(dt);
        //Sjekker etter kollisjon
        Box3 bb;
        bb.setFromObject(tank);
        if (collision::check_collision(bb, land.objects)) {
            tank.position = old_position;
        }

        //For å få powerups på kartet
        Vector3 tank_center;
        bb.getCenter(tank_center);
        for (auto& powerup : powerups) {
            if (!powerup->is_collcted()) {
                powerup->update(dt);

                Vector3 powerup_pos = powerup->get_Position();
                float dx = tank_center.x - powerup_pos.x;
                float dz = tank_center.z - powerup_pos.z;
                float distance = std::sqrt(dx * dx + dz * dz);

                if (distance < 5.0f) { //Hvis tanksen er nærme nok powerupen
                    powerup->collect();
                    key_controls.add_boost();
                }
            }
        }
        camera_follow.update(dt);

        renderer.render(*scene, camera);
    });

    return 0;
}
