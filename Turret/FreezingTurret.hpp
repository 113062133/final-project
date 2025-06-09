#ifndef FREEZINGTURRET_HPP
#define FREEZINGTURRET_HPP
#include "Turret.hpp"

class FreezingTurret : public Turret {
public:
    static const int Price;
    FreezingTurret(float x, float y);
    void CreateBullet() override;
};
#endif   // FREEZINGTURRET_HPP
