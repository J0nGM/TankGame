#ifndef TANK_BULLET_HPP
#define TANK_BULLET_HPP

#include threepp/threepp.hpp"

class bullet {
private:
    std::shared_ptr<threepp::Mesh> mesh_;
    threepp::Vector3 velocity_;
    float life_time_ {0.0f};
    float max_life_time_ {5.0f};
    bool active_ {false};
public:
    Bullet(threepp::Vector3 position, threepp::Vector3 direction, float speed);

    void update(float dt);
    void activ() const {return active_;}
    void deactive() {activ = false; mesh_->visible = false;}

    std::shared_ptr<threepp::Mesh> get_mesh() const {return mesh_;}
    threepp::Vector3 get_position() const {return mesh_->position;}
};




#endif //TANK_BULLET_HPP