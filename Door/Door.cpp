#include "Door.hpp"
#include "Engine/Sprite.hpp"
#include "Scene/Playscene.hpp"
#include "Engine/GameEngine.hpp"
#include "Engine/Group.hpp"
#include "Engine/IScene.hpp"
#include "Player/Player.hpp"

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h> // 若有用到圖形元件
#include <allegro5/allegro_image.h>      // 使用 bitmap 必須

Door::Door(std::string img, float x, float y, float w, float h) : Engine::Sprite(img, x, y, w, h), x(x), y(y), w(w), h(h),
                                                                  entered(false), offset(0), state(Closed), animation_count(0) /*playScene(getPlayScene())*/ {}
void Door::Update(float deltaTime)
{
    if (state == Closed)
    {
        offset = 0;
    }
    else if (state == Opening)
    {
        /* while (animation_count<64)
        {
            offset = 32 * (animation_count/(64/6));

        } */
        Engine::GameEngine::GetInstance().ChangeScene("start");
    }
}
void Door::Draw() const
{
    Sprite::Draw();
}

void Door::PlayerEnterDoor()
{
    state = Opening;
    offset = 0;
    animation_count = 0;
}