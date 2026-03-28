#ifndef GAME_H
#define GAME_H
#include <vector>
#include "Map.h"
#include "Player.h"
#include "Enemy.h"
#include "ZBuffer.h"
#include "Renderer.h"

class Game {
public:
    Game();
    void run();

private:
    Map                map_;
    Player             player_;
    std::vector<Enemy> enemies_;
    ZBuffer            zbuf_;
    Renderer           renderer_;
};

#endif
