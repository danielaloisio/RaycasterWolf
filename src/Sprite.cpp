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

const char* GUN_IDLE[32] = {
    "................","................",
    "................","................",
    "......GGGGG.....","....GBBBBBg.....",
    ".....GBBBBBg....","......ggggg.....",
    "......GBBBg.....","......GBBBg.....",
    "......GBBBg.....","......GBBBg.....",
    "......GBBBg.....","......GBBBg.....",
    "......GBBBg.....","....GGGBBBGGg...",
    "...GBBBBBBBBBG..","...GBBBgggBBBG..",
    "...GBBGgggGBBG..","...GBBGgggGBBG..",
    "...GBBGgggGBBG..","...GBBGMMMGBBG..",
    "...GBBGMMMGBBG..","....gGGMMMGGg...",
    ".....BBGGGBB....","....BBgggBB.....",
    ".....BBgggBB....","....BBgggBB.....",
    ".....gGGGGGg....","................",
    "................","................",
};

const char* GUN_FIRE[32] = {
    "......YYYY......",".....YYYYYY.....",
    "....YYYYYYYY....","....YYYYYYYY....",
    "......GGGGG.....","....GBBBBBg.....",
    ".....GBBBBBg....","......ggggg.....",
    "......GBBBg.....","......GBBBg.....",
    "......GBBBg.....","......GBBBg.....",
    "......GBBBg.....","......GBBBg.....",
    "....GGGBBBGGg...","...GBBBBBBBBBG..",
    "...GBBBgggBBBG..","...GBBGgggGBBG..",
    "...GBBGgggGBBG..","...GBBGgggGBBG..",
    "...GBBGMMMGBBG..","...GBBGMMMGBBG..",
    "....gGGMMMGGg...","....BBGGGBB.....",
    ".....BBgggBB....","....BBgggBB.....",
    ".....BBgggBB....","....gGGGGGg.....",
    "................","................",
    "................","................",
};

Sprite GunSprite::idle()   { return {GUN_IDLE,  16, 32}; }
Sprite GunSprite::firing() { return {GUN_FIRE,  16, 32}; }

bool GunSprite::decodeColor(char c, Color& out) {
    switch(c) {
        case 'G': out = {200,200,200}; return true;
        case 'g': out = {130,130,130}; return true;
        case 'B': out = { 30, 30, 30}; return true;
        case 'M': out = {100, 60, 20}; return true;
        case 'Y': out = {255,230, 50}; return true;
        default:  return false;
    }
}
