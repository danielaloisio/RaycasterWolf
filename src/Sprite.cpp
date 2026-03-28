#include "Sprite.h"

const char* ENEMY_ALIVE[24] = {
    "........HHHHHH..........",
    ".......HHuuuuHH.........",
    "......HHuuuuuuHH........",
    "......HSSSssSSH.........",
    "......HSESSEsSH.........",
    "......HSSSSSsSH.........",
    "......HSSBBSsH..........",
    ".......HSSSSSH..........",
    "......UUUuuuUUU.........",
    ".....UUUuuuuuUUU........",
    "....UUUuuuuuuuUUU.......",
    "....UUGguuuuuGgUU.......",
    "....UUGGuuuuuGGUU.......",
    ".....UUGGuuuGGUU........",
    "......UUUUuUUUU.........",
    ".....UUuuuuuuUUU........",
    "....UUuuuuuuuuUU........",
    "....UUuuuuuuuuUU........",
    ".....UUuuuuuUUU.........",
    "......UUuuuUUU..........",
    ".......UUuUUU...........",
    "......UUU.UUU...........",
    ".....UU.....UU..........",
    "....UU.......UU.........",
};

const char* ENEMY_DEAD[24] = {
    "........................",
    "........................",
    "........................",
    "........................",
    "........................",
    "........................",
    "........................",
    "........................",
    "........................",
    "........................",
    "........................",
    "..........RR............",
    ".........RRRRr..........",
    "........RRrrrRR.........",
    ".......RRrrUrrRR........",
    "......RRrUUUUUrRR.......",
    ".....RRrUuuuuuUrRR......",
    ".....RruuuuuuuuuRR......",
    ".....RRuuSSuuuuRR.......",
    "......RRSSSSuRR.........",
    ".......RRRRRR...........",
    "........RRR.............",
    "........................",
    "........................",
};

Sprite EnemySprite::alive() { return {ENEMY_ALIVE, 24, 24}; }
Sprite EnemySprite::dead()  { return {ENEMY_DEAD,  24, 24}; }

bool EnemySprite::decodeColor(char c, Color& out) {
    switch(c) {
        case 'S': out = {220,180,140}; return true;
        case 's': out = {170,130, 90}; return true;
        case 'U': out = { 60, 80,160}; return true;
        case 'u': out = { 40, 55,110}; return true;
        case 'H': out = { 80, 70, 60}; return true;
        case 'E': out = { 30, 20, 10}; return true;
        case 'B': out = { 60, 30, 20}; return true;
        case 'G': out = {180,180,180}; return true;
        case 'g': out = {110,110,110}; return true;
        case 'R': out = {200, 30, 20}; return true;
        case 'r': out = {140, 20, 10}; return true;
        default:  return false;
    }
}

const char* GUN_IDLE[24] = {
/*         0         1         2         3  */
/* row  0 */ "................................",
/* row  1 */ "............BBB.................",
/* row  2 */ "...........BBBBg................",
/* row  3 */ "...........BBBBg................",
/* row  4 */ "...........BBBBg................",
/* row  5 */ "...........BBBBg................",
/* row  6 */ "...........BBBBg................",
/* row  7 */ "..........GBBBBGg...............",
/* row  8 */ ".........GGBBBBGGg..............",
/* row  9 */ ".........GGBBBBGGg..............",
/* row 10 */ "........GGGBBBBGGGg.............",
/* row 11 */ "........GGGBBBBGGGg.............",
/* row 12 */ "GGGGGGGGGGGBBBBGGGGGGGGGGGGGGGGg",
/* row 13 */ "GBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBg",
/* row 14 */ "GBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBg",
/* row 15 */ "GBBgggBBBBBBBBBBBBBBBBBBgggBBBBg",
/* row 16 */ "GBBgggBBMMMMMMMMMMMMMBBBgggBBBg.",
/* row 17 */ "GBBBBBBBMMMMMMMMMMMMMBBBBBBBBBg.",
/* row 18 */ "GBBBBBBBMMMMMMMMMMMMMBBBBBBBBBg.",
/* row 19 */ "GBBBBBBBMMMMMMMMMMMMMBBBBBBBBBg.",
/* row 20 */ "GBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBg",
/* row 21 */ "..GGGGGGGGGGGGGGGGGGGGGGGGGGGGg.",
/* row 22 */ "................................",
/* row 23 */ "................................",
};

const char* GUN_FIRE[24] = {
/*         0         1         2         3  */
/* row  0 */ "..........OYO...................",
/* row  1 */ ".........OYYYOO.................",
/* row  2 */ "........OYYYYYYO................",
/* row  3 */ ".......OYYYYYYYYO...............",
/* row  4 */ "........OYYYYYO.................",
/* row  5 */ ".........OYYYY..................",
/* row  6 */ "...........OBB..................",
/* row  7 */ "..........GBBBBGg...............",
/* row  8 */ ".........GGBBBBGGg..............",
/* row  9 */ ".........GGBBBBGGg..............",
/* row 10 */ "........GGGBBBBGGGg.............",
/* row 11 */ "........GGGBBBBGGGg.............",
/* row 12 */ "GGGGGGGGGGGBBBBGGGGGGGGGGGGGGGGg",
/* row 13 */ "GBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBg",
/* row 14 */ "GBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBg",
/* row 15 */ "GBBgggBBBBBBBBBBBBBBBBBBgggBBBBg",
/* row 16 */ "GBBgggBBMMMMMMMMMMMMMBBBgggBBBg.",
/* row 17 */ "GBBBBBBBMMMMMMMMMMMMMBBBBBBBBBg.",
/* row 18 */ "GBBBBBBBMMMMMMMMMMMMMBBBBBBBBBg.",
/* row 19 */ "GBBBBBBBMMMMMMMMMMMMMBBBBBBBBBg.",
/* row 20 */ "GBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBg",
/* row 21 */ "..GGGGGGGGGGGGGGGGGGGGGGGGGGGGg.",
/* row 22 */ "................................",
/* row 23 */ "................................",
};

Sprite GunSprite::idle()   { return {GUN_IDLE,  32, 24}; }
Sprite GunSprite::firing() { return {GUN_FIRE,  32, 24}; }

bool GunSprite::decodeColor(char c, Color& out) {
    switch(c) {
        case 'G': out = {200,200,200}; return true;
        case 'g': out = {130,130,130}; return true;
        case 'B': out = { 30, 30, 30}; return true;
        case 'M': out = {100, 60, 20}; return true;
        case 'Y': out = {255,230, 50}; return true;
        case 'O': out = {255,120,  0}; return true;
        default:  return false;
    }
}
