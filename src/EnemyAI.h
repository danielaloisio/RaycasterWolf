#ifndef ENEMYAI_H
#define ENEMYAI_H
#include <vector>
#include "Enemy.h"
#include "Player.h"
#include "Map.h"
#include "ZBuffer.h"

class EnemyAI {
public:
    static void update(std::vector<Enemy>& enemies, Player& player,
                       const Map& map, double dt);

    static void resolveShot(std::vector<Enemy>& enemies, Player& player,
                            const ZBuffer& zbuf);

private:
    static void updateOne(Enemy& e, Player& player,
                          const Map& map, double dt);
};

#endif
