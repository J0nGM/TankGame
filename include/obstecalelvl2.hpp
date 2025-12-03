#ifndef TANK_OBSTECALELVL2_HPP
#define TANK_OBSTECALELVL2_HPP
#include "threepp/threepp.hpp"
#include <vector>        // Don't know if I need this
#include <memory>        // Don't know if I need this
#include <functional>    // Don't know if I need this

enum class obsticale_type_lvl_2 {
    BARRIER
};
class obsticale_lvl2 {
private:
    std::shared_ptr<threepp::Mesh> mesh_;
    threepp::Vector3 position_;
    obsticale_type_lvl_2 type_;

public:
    obsticale_lvl2(const threepp::Vector3& position, obsticale_type_lvl_2 type);

    std::shared_ptr<threepp::Mesh> get_mesh() const { return mesh_;}
    threepp::Vector3 get_position() const { return position_; }
    obsticale_type_lvl_2 get_type() const { return type_; }
};

class obstacle_manger_lvl2 {
private:
    std::vector<std::unique_ptr<obsticale_lvl2>> obsticale_lvl2_;

public:
    void add_obstical(const threepp::Vector3& position, obsticale_type_lvl_2 type_);
    void add_barrier(const threepp::Vector3& position);

    void spawn_barriers_randomly(
    threepp::Scene& scene,
    std::function<threepp::Vector3(float, float, float)> random_position_func);

    const std::vector<std::unique_ptr<obsticale_lvl2>>& get_obstacles() const { return obsticale_lvl2_; }

    bool check_barrier_collisions();

    void add_to_scene(threepp::Scene& scene);
    void clear_obstacles(threepp::Scene& scene);
};
#endif //TANK_OBSTECALELVL2_HPP