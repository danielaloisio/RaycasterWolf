#ifndef PLAYER_HPP
#define PLAYER_HPP
#include <cstdint>
#include "Map.hpp"

class Player {
public:
    Player() = default;

    void handleInput(const uint8_t* keys, int mouseDeltaX,
                     double dt, const Map& map);
    void tick();
    void fireWeapon();
    void applyDamage(int amount);
    void addKill();

    bool isAlive()  const { return hp_ > 0; }
    bool isFiring() const { return fireTimer_ > 0; }

    double x()        const { return x_; }
    double y()        const { return y_; }
    double angle()    const { return angle_; }
    int    hp()       const { return hp_; }
    int    kills()    const { return kills_; }
    int    hitFlash() const { return hitFlash_; }

private:
    double x_         = 1.5;
    double y_         = 1.5;
    double angle_     = 0.0;
    int    fireTimer_ = 0;
    int    hp_        = 100;
    int    kills_     = 0;
    int    hitFlash_  = 0;
};

#endif
