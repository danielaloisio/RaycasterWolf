#include "Map.h"
#include <cmath>
#include <initializer_list>

constexpr int Map::DATA[GameConfig::MAP_HEIGHT][GameConfig::MAP_WIDTH];

bool Map::inBounds(int mx, int my) const {
    return mx >= 0 && mx < GameConfig::MAP_WIDTH &&
           my >= 0 && my < GameConfig::MAP_HEIGHT;
}

int Map::tileAt(int mx, int my) const {
    if (!inBounds(mx, my)) return 1;
    return DATA[my][mx];
}

bool Map::canMove(double nx, double ny) const {
    constexpr double M = 0.2;
    for (double cx : {nx - M, nx + M})
        for (double cy : {ny - M, ny + M}) {
            int mx = (int)std::floor(cx);
            int my = (int)std::floor(cy);
            if (!inBounds(mx, my)) return false;
            if (DATA[my][mx] != 0) return false;
        }
    return true;
}

bool Map::hasLOS(double ax, double ay, double bx, double by) const {
    double dx = bx - ax, dy = by - ay;
    int steps = (int)(std::sqrt(dx*dx + dy*dy) / 0.05) + 1;
    for (int i = 1; i < steps; ++i) {
        double t = (double)i / steps;
        int mx = (int)std::floor(ax + dx * t);
        int my = (int)std::floor(ay + dy * t);
        if (!inBounds(mx, my)) return false;
        if (DATA[my][mx] != 0) return false;
    }
    return true;
}

Color Map::wallColor(int type, bool dark) {
    static const Color tbl[5][2] = {
        {{  0,  0,  0},{  0,  0,  0}},
        {{180,140,100},{120, 90, 60}},
        {{ 80,160, 80},{ 50,110, 50}},
        {{160, 80, 80},{110, 50, 50}},
        {{ 80,120,180},{ 50, 80,130}},
    };
    int t = (type < 1 || type > 4) ? 1 : type;
    return dark ? tbl[t][1] : tbl[t][0];
}
