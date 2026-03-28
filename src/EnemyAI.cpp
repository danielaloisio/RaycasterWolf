#include "EnemyAI.h"
#include "GameConfig.h"
#include <cmath>
#include <cstdlib>

void EnemyAI::update(std::vector<Enemy>& enemies, Player& player,
                     const Map& map, double dt) {
    for (auto& e : enemies)
        updateOne(e, player, map, dt);
}

void EnemyAI::resolveShot(std::vector<Enemy>& enemies, Player& player,
                           const ZBuffer& zbuf) {
    for (auto& e : enemies) {
        if (e.state == EnemyState::DEAD) continue;

        if (std::abs(e.screenX - GameConfig::SCR_W / 2.0) > 45) continue;

        double dx = e.x - player.x(), dy = e.y - player.y();
        double dist = std::sqrt(dx*dx + dy*dy);

        int col = (int)e.screenX;
        if (col < 0 || col >= GameConfig::SCR_W) continue;
        if (dist > zbuf.get(col) + 0.5) continue;
        if (!Map{}.hasLOS(player.x(), player.y(), e.x, e.y)) continue;

        e.hp--;
        if (e.hp <= 0) {
            e.state      = EnemyState::DEAD;
            e.deathTimer = 60;
            player.addKill();
        }
        break;
    }
}

void EnemyAI::updateOne(Enemy& e, Player& player,
                         const Map& map, double dt) {
    if (e.state == EnemyState::DEAD) {
        if (e.deathTimer > 0) --e.deathTimer;
        return;
    }

    double dx   = player.x() - e.x, dy = player.y() - e.y;
    double dist = std::sqrt(dx*dx + dy*dy);

    bool sees = (dist < 8.0) && map.hasLOS(e.x, e.y, player.x(), player.y());
    if (sees) e.state = EnemyState::CHASE;
    else if (e.state == EnemyState::CHASE && dist > 10.0)
        e.state = EnemyState::PATROL;

    if (e.state == EnemyState::CHASE) {
        if (dist < 0.8 && player.isAlive())
            player.applyDamage((int)(22.0 * dt));

        double spd = 2.0 * dt;
        double toX = dx / dist, toY = dy / dist;
        if (map.canMove(e.x + toX * spd, e.y))            e.x += toX * spd;
        if (map.canMove(e.x,             e.y + toY * spd)) e.y += toY * spd;
    } else {
        e.patrolTimer -= dt;
        double spd = 1.2 * dt;
        double nx2 = e.x + std::cos(e.angle) * spd;
        double ny2 = e.y + std::sin(e.angle) * spd;
        if (map.canMove(nx2, e.y)) e.x = nx2; else e.angle += M_PI * 0.6;
        if (map.canMove(e.x, ny2)) e.y = ny2; else e.angle += M_PI * 0.5;
        if (e.patrolTimer <= 0) {
            e.angle       += M_PI / 2.0 * (1 + rand() % 3);
            e.patrolTimer  = 1.5 + (rand() % 30) / 10.0;
        }
    }
}
