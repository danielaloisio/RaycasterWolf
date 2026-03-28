#ifndef RENDERER_H
#define RENDERER_H
#include <SDL2/SDL.h>
#include <vector>
#include "Player.h"
#include "Map.h"
#include "Enemy.h"
#include "ZBuffer.h"

class Renderer {
public:
    Renderer(const char* title, int w, int h);
    ~Renderer();

    Renderer(const Renderer&) = delete;
    Renderer& operator=(const Renderer&) = delete;

    void clear();
    void present();

    void drawWalls(const Player& p, const Map& map, ZBuffer& zbuf);
    void drawEnemies(const Player& p, std::vector<Enemy>& enemies,
                     const ZBuffer& zbuf);
    void drawGun(const Player& p);
    void drawHUD(const Player& p);

private:
    SDL_Window*   win_ = nullptr;
    SDL_Renderer* ren_ = nullptr;
};

#endif
