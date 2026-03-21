#ifndef GAMECONFIG_HPP
#define GAMECONFIG_HPP
#include <cmath>

struct GameConfig {
    static constexpr int    SCR_W    = 960;
    static constexpr int    SCR_H    = 540;
    static constexpr int    HALF_H   = SCR_H / 2;
    static constexpr double FOV      = M_PI / 3.0;
    static constexpr double MOVE_SPD = 4.5;
    static constexpr double ROT_SPD  = 1;
    static constexpr int    MAP_W    = 16;
    static constexpr int    MAP_H    = 16;
};

#endif
