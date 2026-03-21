#ifndef GAME_HPP
#define GAME_HPP
#include <vector>
#include "Map.hpp"
#include "Player.hpp"
#include "Enemy.hpp"
#include "ZBuffer.hpp"
#include "Renderer.hpp"

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
