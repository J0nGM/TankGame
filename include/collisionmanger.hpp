#ifndef TANK_COLLISION_MANGER_HPP
#define TANK_COLLISION_MANGER_HPP

#include "threepp/threepp.hpp"

//Using forwards declartation to reduce compile time https://stackoverflow.com/questions/4757565/what-are-forward-declarations-in-c
class arena_walls;
class obstacle_manger_lvl2;

class collision_manager {
public:
    static constexpr float enemy_hit_radius {20.0};
    static constexpr float player_hit_radius {5.0};
    static constexpr float pickup_collect_radius {5.0};
    static constexpr float portal_activate_radius {10.0};

    static constexpr float tree_collision_padding {3.0};

    static constexpr float bullet_tree_collision_distance {10.0};
    static constexpr float bullet_barrier_collision_radius {5.0};


    static bool check_tree_collision(
        const threepp::Box3& box,
        const std::vector<std::shared_ptr<threepp::Group>>& objects);

    //Check collision with arena walls
    static bool check_wall_collision(
        const threepp::Box3& box,
        const arena_walls& arena);

    //CHeck the collision with barriers
    static bool check_barrier_collision(
        const threepp::Box3& box,
        const obstacle_manger_lvl2& obstacle_manager);

    static bool check_bullet_tree_collision(
    const threepp::Vector3& bullet_pos,
    const std::vector<std::shared_ptr<threepp::Group>>& objects,
    float collision_distance = 10.0);

    static bool check_bullet_enemy_collision(
        const threepp::Box3& bullet_box,
        const threepp::Box3& enemy_box);

    static float calculate_distance(
        const threepp::Vector3& pos1,
        const threepp::Vector3& pos2);

    static bool check_wall_collision_sphere(
    const threepp::Vector3& center,
    float radius,
    const arena_walls& arena);

    static bool check_barrier_collision_sphere(
        const threepp::Vector3& center,
        float radius,
        const obstacle_manger_lvl2& obstacle_manager);

};

#endif //TANK_COLLISION_MANGER_HPP