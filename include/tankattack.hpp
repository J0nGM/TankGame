#ifndef TANK_TANK_ATTACK_HPP
#define TANK_TANK_ATTACK_HPP

class tank_attack {
private:
    int ammo_{0};
    const int max_ammo_{10};
    float shoot_cooldown_{0.0};
    float shoot_cooldown_time_{0.5};

public:
    void add_ammo(int amount);
    bool can_shoot() const;
    void start_cooldown();
    void use_ammo();
    void update(float dt);

    int get_ammo() const { return ammo_; }
};

#endif