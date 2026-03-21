#include "Game.hpp"
#include "EnemyAI.hpp"
#include "GameConfig.hpp"
#include <SDL2/SDL.h>
#include <cmath>

Game::Game()
    : zbuf_(GameConfig::SCR_W)
    , renderer_("RaycasterWolf", GameConfig::SCR_W, GameConfig::SCR_H)
{
    enemies_ = {
        {13.5,  3.5, M_PI/4,       EnemyState::PATROL, 2, 1.5, 0, 0, 0},
        { 7.5, 13.5, 5*M_PI/4,     EnemyState::PATROL, 2, 1.7, 0, 0, 0},
    };
}

void Game::run() {
    Uint64 last = SDL_GetPerformanceCounter();
    bool running = true;
    SDL_Event ev;

    while (running) {
        Uint64 now = SDL_GetPerformanceCounter();
        double dt  = (double)(now - last) / SDL_GetPerformanceFrequency();
        last = now;
        if (dt > 0.05) dt = 0.05;

        while (SDL_PollEvent(&ev)) {
            if (ev.type == SDL_QUIT) running = false;
            if (ev.type == SDL_KEYDOWN &&
                ev.key.keysym.sym == SDLK_ESCAPE) running = false;
            if (ev.type == SDL_MOUSEBUTTONDOWN &&
                ev.button.button == SDL_BUTTON_LEFT) {
                player_.fireWeapon();
                EnemyAI::resolveShot(enemies_, player_, zbuf_);
            }
        }

        int mx, my;
        SDL_GetRelativeMouseState(&mx, &my);
        player_.handleInput(SDL_GetKeyboardState(nullptr), mx, dt, map_);
        player_.tick();

        EnemyAI::update(enemies_, player_, map_, dt);

        renderer_.clear();
        renderer_.drawWalls(player_, map_, zbuf_);
        renderer_.drawEnemies(player_, enemies_, zbuf_);
        renderer_.drawGun(player_);
        renderer_.drawHUD(player_);
        renderer_.present();
    }
}
