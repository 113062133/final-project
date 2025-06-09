#include <string>
#include <algorithm>

#include "ShieldEnemy.hpp"
#include "allegro5/allegro_primitives.h"
#include "allegro5/color.h"

ShieldEnemy::ShieldEnemy(int x, int y) : Enemy("play/enemy-6.png", x, y, 20, 30, 200, 100), shield(200) {
}
void ShieldEnemy::Hit(float damage) {
    if (shield > 0) {
        float absorbed = std::min(shield, damage);
        shield -= absorbed;
        damage -= absorbed;
        if (damage > 0) {
            Enemy::Hit(damage);
        }
    }
    else {
        Enemy::Hit(damage);
    }
}
void ShieldEnemy::Draw() const {
    Enemy::Draw();
    if (shield > 0) {
        al_draw_circle(Position.x, Position.y, std::min(Size.x, Size.y), al_map_rgba(0, 150, 255, 150), shield / 10);
    }
}