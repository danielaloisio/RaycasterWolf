#include "Player.h"
#include "GameConfig.h"
#include <SDL2/SDL.h>
#include <cmath>

void Player::handleInput(const uint8_t* keys, int mouseDeltaX,
                         double dt, const Map& map) {
    angle_ += mouseDeltaX * GameConfig::ROT_SPD * dt;

    if (!isAlive()) return;

    double dx = std::cos(angle_) * GameConfig::MOVE_SPD * dt;
    double dy = std::sin(angle_) * GameConfig::MOVE_SPD * dt;
    double sx = std::cos(angle_ - M_PI / 2.0) * GameConfig::MOVE_SPD * dt;
    double sy = std::sin(angle_ - M_PI / 2.0) * GameConfig::MOVE_SPD * dt;

    if (keys[SDL_SCANCODE_W] || keys[SDL_SCANCODE_UP]) {
        if (map.canMove(x_ + dx, y_)) x_ += dx;
        if (map.canMove(x_, y_ + dy)) y_ += dy;
    }
    if (keys[SDL_SCANCODE_S] || keys[SDL_SCANCODE_DOWN]) {
        if (map.canMove(x_ - dx, y_)) x_ -= dx;
        if (map.canMove(x_, y_ - dy)) y_ -= dy;
    }
    if (keys[SDL_SCANCODE_A]) {
        if (map.canMove(x_ + sx, y_)) x_ += sx;
        if (map.canMove(x_, y_ + sy)) y_ += sy;
    }
    if (keys[SDL_SCANCODE_D]) {
        if (map.canMove(x_ - sx, y_)) x_ -= sx;
        if (map.canMove(x_, y_ - sy)) y_ -= sy;
    }
}

void Player::tick() {
    if (fireTimer_ > 0) --fireTimer_;
    if (hitFlash_ > 0) --hitFlash_;
    if (hp_ < 0) hp_ = 0;
}

void Player::fireWeapon() {
    if (!isAlive()) return;
    fireTimer_ = 8;
}

void Player::applyDamage(int amount) {
    hp_ -= amount;
    hitFlash_ = 12;
}

void Player::addKill() { ++kills_; }
