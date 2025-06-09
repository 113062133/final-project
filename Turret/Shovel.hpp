#ifndef SHOVEL_HPP
#define SHOVEL_HPP
#include "Turret.hpp"

class Shovel : public Turret {
public:
    Shovel(float x, float y);
    void CreateBullet() override;
};
#endif   // SHOVEL_HPP