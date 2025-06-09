#include <allegro5/base.h>
#include <cmath>
#include <string>

#include "Bullet/FreezingBullet.hpp"
#include "Engine/AudioHelper.hpp"
#include "Engine/Group.hpp"
#include "Engine/Point.hpp"
#include "FreezingTurret.hpp"
#include "Scene/PlayScene.hpp"

const int FreezingTurret::Price = 300;
FreezingTurret::FreezingTurret(float x, float y)
    : Turret("play/tower-base.png", "play/turret-6.png", x, y, 200, Price, 3.0) {
    // Move center downward, since we the turret head is slightly biased upward.
    Anchor.y += 8.0f / GetBitmapHeight();
}
void FreezingTurret::CreateBullet() {
    Engine::Point diff = Engine::Point(cos(Rotation - ALLEGRO_PI / 2), sin(Rotation - ALLEGRO_PI / 2));
    float rotation = atan2(diff.y, diff.x);
    Engine::Point normalized = diff.Normalize();
    Engine::Point normal = Engine::Point(-normalized.y, normalized.x);
    // Change bullet position to the front of the gun barrel.
    getPlayScene()->BulletGroup->AddNewObject(new FreezingBullet(Position + normalized * 36 - normal * 6, diff, rotation, this));
    AudioHelper::PlayAudio("missile.wav");
}