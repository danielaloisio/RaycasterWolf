#ifndef SPRITE_HPP
#define SPRITE_HPP
#include "Color.hpp"

struct Sprite {
    const char* const* rows;
    int width;
    int height;

    char pixelAt(int row, int col) const { return rows[row][col]; }
};

extern const char* ENEMY_ALIVE[24];
extern const char* ENEMY_DEAD[24];

struct EnemySprite {
    static Sprite alive();
    static Sprite dead();
    static bool decodeColor(char c, Color& out);
};

extern const char* GUN_IDLE[32];
extern const char* GUN_FIRE[32];

struct GunSprite {
    static Sprite idle();
    static Sprite firing();
    static bool decodeColor(char c, Color& out);
};

#endif
