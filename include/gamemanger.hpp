#ifndef TANK_GAMEMANGER_HPP
#define TANK_GAMEMANGER_HPP

#include <threepp/threepp.hpp>
#include <vector>
#include <memory>
#include <cmath>
#include "tank.hpp"
#include "keycontrolls.hpp"
#include "landscape.hpp"
#include "camercontrolls.hpp"
#include "boost.hpp"
#include "bullet.hpp"
#include "ammo.hpp"
#include "portalLVL2.hpp"
#include "landscape2.hpp"
#include "enemy.hpp"

class game_manger {
private:
    threepp::Scene& scene_;
    Tank& tank_;
    Key_controlls& key_controlls_;
    Landscape& landscape_;
    Camera_follow& camera_follow_;

    std::vector<std::unique_ptr<power_up_boost>> powerups_;
    std::vector<std::unique_ptr<ammo>> ammo_;
    std::vector<std::unique_ptr<bullet>> bullets_;

    std::vector<std::unique_ptr<bullet>> enemy_bullets_;
    std::vector<std::unique_ptr<Enemy>> enemies_;

    int player_hp_ {8};
    bool game_over_ {false};

    std::unique_ptr<portal_lvl2> portal_;
    int current_level_ {1};
    bool level_completed_ {false};

    std::shared_ptr<threepp::Mesh> level2_ground_;
    std::vector<std::shared_ptr<threepp::Object3D>> level2_objects_;


public:
    game_manger(
        threepp::Scene& scene,
        Tank& tank,
        Key_controlls& key_controls,
        Landscape& land,
        Camera_follow& camera_follow);

    void setup_powerups(int num_powerups);
    void setup_ammo(int num_ammo);
    void update(float dt);

    bool all_trees_destroyed() const;
    int get_current_level() const { return current_level_;}
    bool is_level_completed() const { return level_completed_;}

    void setup_enemies(int count);
    void update_enemies(float dt);
    void enemy_shooting();
    void update_enemy_bullets(float dt);
    void check_player_hit();
    void check_enemy_hit();

    int get_player_hp() const { return player_hp_; }
    bool is_game_over() const {return game_over_;}


private:
    void handle_tank_movement(float dt);
    void handle_shooting();
    void update_bullets(float dt);
    void cleanup_bullets();
    void handle_powerup_collisions();
    void handle_ammo_collisions();
    void bullet_collisions_with_tree();
    void check_enemy_collisions();

    void check_portal_spawn();
    void portal_entry();
    void load_level_2();
    void clean_level();

    float calculate_distance(
        const threepp::Vector3& pos1,
        const threepp::Vector3& pos2) {
        float dx = pos1.x - pos2.x;
        float dz = pos1.z - pos2.z;
        return std::sqrt(dx * dx + dz * dz);
    }

    threepp::Vector3 random_position(float range_x = 400.0f, float y = 3.0f, float range_z = 400.0f);

    //AI got littel assistance with creating this funciton, so that it can be used for any object type
template<typename T>
    void spawn_item_pickup(std::vector<std::unique_ptr<T>>& container, int count) {
    for (int i = 0; i < count; i++) {
        auto pickup = std::make_unique<T>(random_position());
        scene_.add(pickup->getMesh());
        container.push_back(std::move(pickup));
    }
}

};

#endif //TANK_GAMEMANGER_HPP
