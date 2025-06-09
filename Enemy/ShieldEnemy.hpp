#ifndef SHIELDENEMY_HPP
#define SHIELDENEMY_HPP
#include "Enemy.hpp"

class ShieldEnemy : public Enemy {
public:
    ShieldEnemy(int x, int y);
    void Hit(float damage) override;
    void Draw() const override;
    int GetShield() const;

protected:
    float shield;
};
#endif   // SHIELDENEMY_HPP
