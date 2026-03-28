#ifndef ENEMY_H
#define ENEMY_H

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
