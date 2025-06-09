#ifndef LANDMINE_HPP
#define LANDMINE_HPP
#include "Turret.hpp"

class Landmine : public Turret {
public:
    static const int Price;
    Landmine(float x, float y);
    void CreateBullet() override;
    void Update(float deltaTime) override;
    bool placed = false;
};
#endif   // LANDMINE_HPP
