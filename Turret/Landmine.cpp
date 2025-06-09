#include <allegro5/base.h>
#include <cmath>
#include <string>

#include "Engine/AudioHelper.hpp"
#include "Engine/Group.hpp"
#include "Engine/Point.hpp"
#include "Landmine.hpp"
#include "Enemy/Enemy.hpp"
#include "Engine/Sprite.hpp"
#include "Scene/PlayScene.hpp"
#include "UI/Animation/ExplosionEffect.hpp"
#include "UI/Animation/DirtyEffect.hpp"

const int Landmine::Price = 100;
Landmine::Landmine(float x, float y)
    : Turret("play/tool-base.png", "play/turret-fire.png", x, y, 0, Price, 0) {
    // Move center downward, since we the turret head is slightly biased upward.
    Anchor.y += 8.0f / GetBitmapHeight();
}
void Landmine::CreateBullet() {}
void Landmine::Update(float deltaTime) {
    Sprite::Update(deltaTime);
    if (!placed) return;
    PlayScene* scene = getPlayScene();

    for (auto& obj1 : scene->EnemyGroup->GetObjects()) {
        Enemy* enemy = dynamic_cast<Enemy*>(obj1);
        if (!enemy) continue;

        float dx = Position.x - enemy->Position.x;
        float dy = Position.y - enemy->Position.y;
        float distance = std::sqrt(dx * dx + dy * dy);

        if (distance <= 100) {
            for (auto& obj2 : scene->EnemyGroup->GetObjects()) {
                Enemy* e = dynamic_cast<Enemy*>(obj2);
                if (!e) continue;

                float edx = Position.x - e->Position.x;
                float edy = Position.y - e->Position.y;
                float edistance = std::sqrt(edx * edx + edy * edy);
                if (edistance <= 100) {
                    e->Hit(100);
                }
            }

            scene->EffectGroup->AddNewObject(new ExplosionEffect(Position.x, Position.y));
            scene->EffectGroup->AddNewObject(new ExplosionEffect(Position.x - 50, Position.y));
            scene->EffectGroup->AddNewObject(new ExplosionEffect(Position.x + 50, Position.y));
            scene->EffectGroup->AddNewObject(new ExplosionEffect(Position.x - 25, Position.y - 50));
            scene->EffectGroup->AddNewObject(new ExplosionEffect(Position.x + 25, Position.y - 50));
            scene->EffectGroup->AddNewObject(new ExplosionEffect(Position.x - 25, Position.y + 50));
            scene->EffectGroup->AddNewObject(new ExplosionEffect(Position.x + 25, Position.y + 50));
            AudioHelper::PlaySample("explosion.wav");
            getPlayScene()->TowerGroup->RemoveObject(GetObjectIterator());
            scene->GroundEffectGroup->AddNewObject(new Engine::Sprite("play/explosion-4.png", Position.x, Position.y));
            return;
        }
    }
}
