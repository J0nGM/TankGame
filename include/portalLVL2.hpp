#ifndef TANK_PORTALLVL2_HPP
#define TANK_PORTALLVL2_HPP

#include <threepp/threepp.hpp>

class portal_lvl2 {
private:
    std::shared_ptr<threepp::Mesh>mesh_;
    bool activated_{false};
    float time_{0.0};

public:
    portal_lvl2(threepp::Vector3 position);
    void update(float dt);
    bool is_activated() const {return activated_;}

    void activate() {
        activated_ = true;
    }
    std::shared_ptr<threepp::Mesh>get_mesh() {return mesh_;}
    threepp::Vector3 get_position() const  {return mesh_->position; }
};

#endif //TANK_PORTALLVL2_HPP