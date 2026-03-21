#ifndef ENEMYAI_HPP
#define ENEMYAI_HPP
#include <vector>
#include "Enemy.hpp"
#include "Player.hpp"
#include "Map.hpp"
#include "ZBuffer.hpp"

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
