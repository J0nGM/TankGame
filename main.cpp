#include <iostream>
#include <threepp/threepp.hpp>
#include "tank.hpp"
#include "keyinputhandler.hpp"
#include "landscape.hpp"
#include "windowresize.hpp"
#include "camercontrolls.hpp"
#include "gamemanger.hpp"
#include "imguihandler.hpp"
#include "landscape.hpp"

using namespace threepp;

void setup_scene(Scene &scene) {
    scene.background = Color::aliceblue;
    auto light = HemisphereLight::create(0xffffbb, 0x080820);
    scene.add(light);
}

void setup_landscape(Scene &scene, Landscape &land) {
    land.groundMesh->position.y = -0.5f;
    land.groundMesh->receiveShadow = true;
    scene.add(land.groundMesh);

    for (const auto &road: land.roads) {
        scene.add(road);
    }
}

void setup_tank(Scene &scene, tank &tank) {
    tank.position.y = 5.0f;
    scene.add(tank);
}

int main() {
    Canvas canvas;
    GLRenderer renderer(canvas.size());

    PerspectiveCamera camera(45, canvas.aspect(), 0.1, 10000);
    camera.position.set(0, 50, 100);

    window_resize_handler resizeHandler(camera, renderer);
    canvas.onWindowResize(resizeHandler);

    auto scene = Scene::create();
    setup_scene(*scene);

    tank player_tank("../assets/3Dmodell/viecal/Tank.glb", *scene);

    key_input_handler key_controls;
    canvas.addKeyListener(key_controls);

    Camera_follow camera_follow(camera, player_tank, key_controls, Vector3(60, 20, 0));

    Landscape land;
    setup_landscape(*scene, land);

    game_manger game(
        *scene,
        player_tank,
        key_controls,
        camera_follow,
        land,
        [](float range_x, float y, float range_z) {
            float random_x = (rand() % static_cast<int>(range_x)) - (range_x / 2);
            float random_z = (rand() % static_cast<int>(range_z)) - (range_z / 2);
            return Vector3(random_x, y, random_z);
        }
    );

    imgui_handler imgui;
    imgui.init(reinterpret_cast<GLFWwindow *>(canvas.windowPtr()));

    Clock clock;
    canvas.animate([&] {
        float dt = clock.getDelta();
        game.update(dt);
        renderer.render(*scene, camera);

        imgui.begin_frame();
        imgui.render_ui(game);

        bool should_quit = false;
        game.handle_menus(imgui, should_quit);
        if (should_quit) {
            canvas.close();
        }

        imgui.end_frame();
    });

    return 0;
}
