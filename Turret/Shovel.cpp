#include <allegro5/base.h>
#include <string>

#include "Engine/Point.hpp"
#include "Shovel.hpp"
#include "Scene/PlayScene.hpp"

Shovel::Shovel(float x, float y)
    : Turret("play/tool-base.png", "play/shovel.png", x, y, 0, 0, 0) {
    // Move center downward, since we the turret head is slightly biased upward.
    Anchor.y += 8.0f / GetBitmapHeight();
}

void Shovel::CreateBullet() {}
