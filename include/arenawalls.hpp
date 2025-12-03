#ifndef TANK_ARENAWALLS_HPP
#define TANK_ARENAWALLS_HPP

#include "threepp/threepp.hpp"

class arena_walls {
public:
    arena_walls();

    void add_walls_to_scene(threepp::Scene &scene, float arena_size);

    void clear_walls(threepp::Scene &scene);

    bool check_collision(const threepp::Box3 &box) const;

    const std::vector<std::shared_ptr<threepp::Mesh> > &get_walls() const { return walls_; }

    float get_arena_size() const { return arena_size_; }

    void remove_walls_from_scene(threepp::Scene &scene);

private:
    std::vector<std::shared_ptr<threepp::Mesh> > walls_;
    float arena_size_{250.0};

    void create_single_wall(
        threepp::Scene &scene,
        std::shared_ptr<threepp::BufferGeometry> geometry,
        std::shared_ptr<threepp::Material> material,
        const threepp::Vector3 &position);

    const float wall_height_{40.0};
    const float wall_thickness_{5.0};
    const float wall_depth_{2.0};
};

#endif //TANK_ARENAWALLS_HPP
