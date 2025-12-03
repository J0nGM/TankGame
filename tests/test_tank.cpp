#include "tank.hpp"
#include "tankattack.hpp"
#include "bulletmanager.hpp"
#include "tankmovment.hpp"
#include "boost.hpp"
#include "ammo.hpp"
#include "levelmanger.hpp"
#include "enemymanager.hpp"
#include "collisionmanger.hpp"
#include "threepp/threepp.hpp"
#include <catch2/catch_test_macros.hpp>

using namespace threepp;

TEST_CASE("Tank creation") {
    auto scene = Scene::create();
    tank tank("../assets/3Dmodell/viecal/Tank.glb", *scene);

    REQUIRE(tank.mesh != nullptr);
}

TEST_CASE("Moving forwards") {
    auto scene = Scene::create();
    tank tank("../assets/3Dmodell/viecal/Tank.glb", *scene);
    float start_in_Z = tank.mesh->position.z;
    tank.mesh->translateZ(1.0f); // Move forward

    REQUIRE(tank.mesh->position.z < start_in_Z);
}

TEST_CASE("Shooting bullets") {
    bullet_manager bullets;
    auto scene = Scene::create();

    bullets.spawn_bullet(*scene, Vector3(0, 0, 0), Vector3(1, 0, 0), 200.0f);

    REQUIRE(bullets.get_bullets().size() == 1);
}

TEST_CASE("Tree creation") {
    Landscape landscape;
    REQUIRE(landscape.objects.size() ==0 ); //To check if the landscap start empti

    landscape.add_tree(Vector3(10, 0, 10));

    REQUIRE(landscape.objects.size() == 1); //Check if the tree is added
}

TEST_CASE("Tree destroyed") {
    auto scene = Scene::create();
    bullet_manager bullets;
    Landscape landscape;

    Vector3 tree_position(6, 0, 7);
    landscape.add_tree(tree_position);
    REQUIRE(landscape.objects[0]->visible == true);

    Vector3 bullet_direction(1, 0, 1);
    bullet_direction.normalize();

    Vector3 bullet_position = tree_position - bullet_direction * 5.0f;
    bullets.spawn_bullet(*scene, bullet_position, bullet_direction, 200.0f);//Got help from AI to calculate the position

    bullets.update(0.02f);

    bool hit = collision_manager::check_bullet_tree_collision(
    bullets.get_bullets()[0]->get_position(),
    landscape.objects
);

    if (hit) {
        bullets.get_bullets()[0]->deactivate();
    }

    REQUIRE(hit);
    REQUIRE(landscape.objects[0]->visible == false);
}

TEST_CASE("Enemy manager spawns correct number") {
    auto scene = Scene::create();
    enemy_manager enemies;

    enemies.spawn_enemies(*scene, 5, 6, 7);

    REQUIRE(enemies.all_destroyed() == false);
}

TEST_CASE("Enemy takes damage") {
    auto scene = Scene::create();
    enemy_manager enemies;
    bullet_manager bullets;

    enemies.spawn_enemies(*scene, 5, 1, 1);

    bullets.spawn_bullet(*scene, Vector3(0, 12.5f, 0), Vector3(1, 0, 0), 200.0f);

    int hits = enemies.check_bullet_hits(bullets.get_bullets());

    REQUIRE(hits >= 0);
}

TEST_CASE("Tank collision radius") {
    tank tank("../assets/3Dmodell/viecal/Tank.glb", *Scene::create());
    Vector3 pos1(0, 0, 0);
    Vector3 pos2(5, 0, 0);

    float distance = collision_manager::calculate_distance(pos1, pos2);
    REQUIRE(distance == 5.0f);
}

TEST_CASE("Tank cannot shoot without ammo") {
    tank_attack attack;

    REQUIRE(attack.can_shoot() == false);

    attack.add_ammo(1);
    REQUIRE(attack.can_shoot() == true);
    REQUIRE(attack.get_ammo() == 1);

    attack.use_ammo();
    REQUIRE(attack.get_ammo() == 0);
    REQUIRE(attack.can_shoot() == false);
}

TEST_CASE("Boost stacking") {
    tank tank_obj("../assets/3Dmodell/viecal/Tank.glb", *Scene::create());


    tank_movement movement(tank_obj);

    movement.add_boost();
    float time1 = movement.get_boost_time_left();
    REQUIRE(time1 > 0.0f);

    movement.add_boost();
    float time2 = movement.get_boost_time_left();
    REQUIRE(time2 > time1);
}

TEST_CASE("Power-up collection") {
    power_up_boost boost(Vector3(0, 3, 0));

    REQUIRE(boost.is_collected() == false);
    REQUIRE(boost.getMesh()->visible == true);

    boost.collect();

    REQUIRE(boost.is_collected() == true);
    REQUIRE(boost.getMesh()->visible == false);
}

TEST_CASE("Ammo collection") {
    ammo ammo_pickup(Vector3(0, 3, 0));

    REQUIRE(ammo_pickup.is_collected() == false);
    REQUIRE(ammo_pickup.get_ammo_amount() == 2);

    ammo_pickup.collect();

    REQUIRE(ammo_pickup.is_collected() == true);
}
