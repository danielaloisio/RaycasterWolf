#ifndef ENEMY_HPP
#define ENEMY_HPP

enum class EnemyState { PATROL, CHASE, DEAD };

struct Enemy {
    double     x, y;
    double     angle;
    EnemyState state;
    int        hp;
    double     patrolTimer;
    int        deathTimer;
    double     screenX;
    double     dist;
};

#endif
