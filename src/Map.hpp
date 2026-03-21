#ifndef MAP_HPP
#define MAP_HPP
#include "Color.hpp"
#include "GameConfig.hpp"

class Map {
public:
    bool inBounds(int mx, int my) const;
    int  tileAt(int mx, int my) const;
    bool canMove(double nx, double ny) const;
    bool hasLOS(double ax, double ay, double bx, double by) const;

    static Color wallColor(int type, bool dark);

private:
    static constexpr int DATA[GameConfig::MAP_H][GameConfig::MAP_W] = {
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,2,2,0,0,0,3,3,0,0,4,0,4,0,1},
        {1,0,2,0,0,0,0,0,3,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,4,0,4,0,1},
        {1,0,0,0,1,1,0,0,0,1,1,0,0,0,0,1},
        {1,0,0,0,1,0,0,0,0,0,1,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,3,0,0,0,0,0,0,0,0,0,2,0,0,1},
        {1,0,3,3,0,1,0,0,0,1,0,0,0,0,0,1},
        {1,0,0,0,0,1,1,1,1,1,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,4,4,0,1},
        {1,0,4,0,0,0,2,2,2,0,0,0,0,4,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    };
};

#endif
