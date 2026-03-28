#include "Renderer.h"
#include "GameConfig.h"
#include "Sprite.h"
#include <cmath>
#include <algorithm>

Renderer::Renderer(const char* title, int w, int h) {
    SDL_Init(SDL_INIT_VIDEO);
    win_ = SDL_CreateWindow(title,
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        w, h, SDL_WINDOW_SHOWN);
    ren_ = SDL_CreateRenderer(win_, -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    SDL_SetRelativeMouseMode(SDL_TRUE);
}

Renderer::~Renderer() {
    SDL_DestroyRenderer(ren_);
    SDL_DestroyWindow(win_);
    SDL_Quit();
}

void Renderer::clear() {
    SDL_SetRenderDrawColor(ren_, 0, 0, 0, 255);
    SDL_RenderClear(ren_);
}

void Renderer::present() { SDL_RenderPresent(ren_); }

void Renderer::drawWalls(const Player& p, const Map& map, ZBuffer& zbuf) {
    zbuf.reset();

    SDL_SetRenderDrawColor(ren_, 50, 50, 60, 255);
    SDL_Rect top = {0, 0, GameConfig::SCR_W, GameConfig::HALF_H};
    SDL_RenderFillRect(ren_, &top);
    SDL_SetRenderDrawColor(ren_, 70, 55, 40, 255);
    SDL_Rect bot = {0, GameConfig::HALF_H, GameConfig::SCR_W, GameConfig::HALF_H};
    SDL_RenderFillRect(ren_, &bot);

    double startAngle = p.angle() - GameConfig::FOV / 2.0;

    for (int col = 0; col < GameConfig::SCR_W; ++col) {
        double rayAngle = startAngle + (double)col / GameConfig::SCR_W * GameConfig::FOV;
        double cosA = std::cos(rayAngle);
        double sinA = std::sin(rayAngle);

        int mapX = (int)p.x(), mapY = (int)p.y();
        double ddx = (cosA == 0) ? 1e30 : std::abs(1.0 / cosA);
        double ddy = (sinA == 0) ? 1e30 : std::abs(1.0 / sinA);
        int stepX, stepY;
        double sdx, sdy;

        if (cosA < 0) { stepX = -1; sdx = (p.x() - mapX) * ddx; }
        else          { stepX =  1; sdx = (mapX + 1.0 - p.x()) * ddx; }
        if (sinA < 0) { stepY = -1; sdy = (p.y() - mapY) * ddy; }
        else          { stepY =  1; sdy = (mapY + 1.0 - p.y()) * ddy; }

        bool hit = false, sideY = false;
        int wallType = 0;
        while (!hit) {
            if (sdx < sdy) { sdx += ddx; mapX += stepX; sideY = false; }
            else           { sdy += ddy; mapY += stepY; sideY = true;  }
            if (!map.inBounds(mapX, mapY)) break;
            wallType = map.tileAt(mapX, mapY);
            if (wallType > 0) hit = true;
        }

        if (!hit) { zbuf.set(col, 1e30); continue; }

        double perpDist = sideY ? (sdy - ddy) : (sdx - ddx);
        perpDist *= std::cos(rayAngle - p.angle());
        if (perpDist < 0.001) perpDist = 0.001;
        zbuf.set(col, perpDist);

        int lineH     = (int)(GameConfig::SCR_H / perpDist);
        int drawStart = std::max(0, GameConfig::HALF_H - lineH / 2);
        int drawEnd   = std::min(GameConfig::SCR_H - 1, GameConfig::HALF_H + lineH / 2);

        Color c = Map::wallColor(wallType, sideY);
        float shade = std::max(0.05f, std::min(1.0f, 4.0f / (float)perpDist));
        SDL_SetRenderDrawColor(ren_,
            (uint8_t)(c.r * shade),
            (uint8_t)(c.g * shade),
            (uint8_t)(c.b * shade), 255);
        SDL_RenderDrawLine(ren_, col, drawStart, col, drawEnd);
    }
}

void Renderer::drawEnemies(const Player& p, std::vector<Enemy>& enemies,
                            const ZBuffer& zbuf) {
    for (auto& e : enemies) {
        double dx = e.x - p.x(), dy = e.y - p.y();
        e.dist = std::sqrt(dx*dx + dy*dy);
    }
    std::sort(enemies.begin(), enemies.end(),
              [](const Enemy& a, const Enemy& b){ return a.dist > b.dist; });

    double planeX = -std::sin(p.angle()) * std::tan(GameConfig::FOV / 2.0);
    double planeY =  std::cos(p.angle()) * std::tan(GameConfig::FOV / 2.0);
    double dirX   =  std::cos(p.angle());
    double dirY   =  std::sin(p.angle());

    for (auto& e : enemies) {
        double dx = e.x - p.x(), dy = e.y - p.y();
        double invDet = 1.0 / (planeX * dirY - dirX * planeY);
        double transX =  invDet * ( dirY * dx - dirX * dy);
        double transY =  invDet * (-planeY * dx + planeX * dy);

        if (transY <= 0.1) continue;

        int spriteScreenX = (int)((GameConfig::SCR_W / 2.0) * (1.0 + transX / transY));
        e.screenX = spriteScreenX;

        Sprite spr = (e.state == EnemyState::DEAD)
                   ? EnemySprite::dead() : EnemySprite::alive();
        int sprH = std::abs((int)(GameConfig::SCR_H / transY));
        int sprW = sprH;
        int drawStartY = GameConfig::HALF_H - sprH / 2;
        int drawStartX = spriteScreenX - sprW / 2;

        float shade = std::max(0.08f, std::min(1.0f, 3.5f / (float)transY));

        for (int sx = 0; sx < sprW; ++sx) {
            int screenX = drawStartX + sx;
            if (screenX < 0 || screenX >= GameConfig::SCR_W) continue;
            if (transY >= zbuf.get(screenX)) continue;

            int texX = sx * spr.width / sprW;
            if (texX >= spr.width) continue;

            for (int sy = 0; sy < sprH; ++sy) {
                int screenY = drawStartY + sy;
                if (screenY < 0 || screenY >= GameConfig::SCR_H) continue;
                int texY = sy * spr.height / sprH;
                if (texY >= spr.height) continue;

                char ch = spr.pixelAt(texY, texX);
                Color col;
                if (!EnemySprite::decodeColor(ch, col)) continue;
                SDL_SetRenderDrawColor(ren_,
                    (uint8_t)(col.r * shade),
                    (uint8_t)(col.g * shade),
                    (uint8_t)(col.b * shade), 255);
                SDL_RenderDrawPoint(ren_, screenX, screenY);
            }
        }
    }
}

void Renderer::drawGun(const Player& p) {
    Sprite spr = p.isFiring() ? GunSprite::firing() : GunSprite::idle();
    const int SCALE = 5;
    int offX = GameConfig::SCR_W / 2 - (spr.width * SCALE) / 2 + 15;
    int offY = GameConfig::SCR_H - spr.height * SCALE - (-10);
    for (int row = 0; row < spr.height; ++row) {
        const char* line = spr.rows[row];
        for (int col = 0; col < spr.width && line[col]; ++col) {
            Color c;
            if (!GunSprite::decodeColor(line[col], c)) continue;
            SDL_Rect r = { offX + col * SCALE, offY + row * SCALE, SCALE, SCALE };
            SDL_SetRenderDrawColor(ren_, c.r, c.g, c.b, 255);
            SDL_RenderFillRect(ren_, &r);
        }
    }
}

void Renderer::drawHUD(const Player& p) {
    if (p.hitFlash() > 0) {
        SDL_SetRenderDrawBlendMode(ren_, SDL_BLENDMODE_BLEND);
        SDL_SetRenderDrawColor(ren_, 200, 0, 0,
            (uint8_t)std::min(160, p.hitFlash() * 12));
        SDL_Rect full = {0, 0, GameConfig::SCR_W, GameConfig::SCR_H};
        SDL_RenderFillRect(ren_, &full);
        SDL_SetRenderDrawBlendMode(ren_, SDL_BLENDMODE_NONE);
    }

    int cx = GameConfig::SCR_W / 2, cy = GameConfig::SCR_H / 2;
    SDL_SetRenderDrawColor(ren_, 220, 220, 220, 255);
    SDL_RenderDrawLine(ren_, cx - 10, cy, cx -  4, cy);
    SDL_RenderDrawLine(ren_, cx +  4, cy, cx + 10, cy);
    SDL_RenderDrawLine(ren_, cx, cy - 10, cx, cy -  4);
    SDL_RenderDrawLine(ren_, cx, cy +  4, cx, cy + 10);

    SDL_SetRenderDrawColor(ren_, 60, 10, 10, 255);
    SDL_Rect hpBg = {20, GameConfig::SCR_H - 30, 200, 18};
    SDL_RenderFillRect(ren_, &hpBg);
    int hpW = (int)(200.0 * p.hp() / 100.0);
    int gr  = (int)(40 + 160 * (1.0 - p.hp() / 100.0));
    int gg  = (int)(160 * p.hp() / 100.0);
    SDL_SetRenderDrawColor(ren_, (uint8_t)gr, (uint8_t)gg, 20, 255);
    SDL_Rect hpFg = {20, GameConfig::SCR_H - 30, hpW, 18};
    SDL_RenderFillRect(ren_, &hpFg);
    SDL_SetRenderDrawColor(ren_, 200, 200, 200, 255);
    SDL_RenderDrawRect(ren_, &hpBg);

    auto drawDigit = [&](int n, int ox, int oy, uint8_t r, uint8_t g, uint8_t b) {
        static const uint8_t font[10][5] = {
            {0b111,0b101,0b101,0b101,0b111},
            {0b010,0b110,0b010,0b010,0b111},
            {0b111,0b001,0b111,0b100,0b111},
            {0b111,0b001,0b111,0b001,0b111},
            {0b101,0b101,0b111,0b001,0b001},
            {0b111,0b100,0b111,0b001,0b111},
            {0b111,0b100,0b111,0b101,0b111},
            {0b111,0b001,0b001,0b001,0b001},
            {0b111,0b101,0b111,0b101,0b111},
            {0b111,0b101,0b111,0b001,0b111},
        };
        int d = n % 10;
        SDL_SetRenderDrawColor(ren_, r, g, b, 255);
        for (int row = 0; row < 5; ++row)
            for (int bit = 2; bit >= 0; --bit)
                if (font[d][row] & (1 << bit)) {
                    SDL_Rect px = {ox + (2 - bit) * 3, oy + row * 3, 2, 2};
                    SDL_RenderFillRect(ren_, &px);
                }
    };

    drawDigit((p.hp() / 100) % 10, 20, GameConfig::SCR_H - 52, 255, 200, 200);
    drawDigit((p.hp() /  10) % 10, 34, GameConfig::SCR_H - 52, 255, 200, 200);
    drawDigit( p.hp()        % 10, 48, GameConfig::SCR_H - 52, 255, 200, 200);

    int kx = GameConfig::SCR_W - 60, ky = GameConfig::SCR_H - 34;
    if (p.kills() >= 10) drawDigit(p.kills() / 10, kx,      ky, 255, 220, 80);
    drawDigit(p.kills() % 10,                      kx + 14, ky, 255, 220, 80);

    if (!p.isAlive()) {
        SDL_SetRenderDrawBlendMode(ren_, SDL_BLENDMODE_BLEND);
        SDL_SetRenderDrawColor(ren_, 0, 0, 0, 180);
        SDL_Rect ov = {0, 0, GameConfig::SCR_W, GameConfig::SCR_H};
        SDL_RenderFillRect(ren_, &ov);
        SDL_SetRenderDrawBlendMode(ren_, SDL_BLENDMODE_NONE);
        SDL_SetRenderDrawColor(ren_, 200, 30, 30, 255);
        for (int i = 0; i < 8; ++i) {
            SDL_Rect line = {GameConfig::SCR_W/2 - 60 + i*20,
                             GameConfig::SCR_H/2 - 30, 14, 60};
            SDL_RenderFillRect(ren_, &line);
        }
        SDL_SetRenderDrawColor(ren_, 255, 60, 60, 255);
        SDL_Rect msg = {GameConfig::SCR_W/2 - 80, GameConfig::SCR_H/2 - 40, 160, 80};
        SDL_RenderDrawRect(ren_, &msg);
    }
}
