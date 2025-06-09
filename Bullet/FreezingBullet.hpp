#ifndef FREEZINGBULLET_HPP
#define FREEZINGBULLET_HPP
#include "Bullet.hpp"

class Enemy;
class Turret;
namespace Engine {
    struct Point;
}   // namespace Engine

class FreezingBullet : public Bullet {
public:
    explicit FreezingBullet(Engine::Point position, Engine::Point forwardDirection, float rotation, Turret *parent);
    void OnExplode(Enemy *enemy) override;
};
#endif   // FREEZINGBULLET_HPP
