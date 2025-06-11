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


Door::Door(std::string img, float x, float y, float w, float h) :
    Engine::Sprite(img, x, y, w, h),
    x(x), y(y), w(w), h(h),
    entered(false), offset(0), state(Closed), animation_count(0),
    currentFrame(0), frameTimer(0) {}


void Door::Update(float deltaTime) {
    /* if (state == Closed) {
        animation_count = 0;
    }
    else if (state == Opening) {
        //frameTimer += deltaTime;
        animation_count = animation_count + 1;
        if(animation_count >= 64){
            animation_count = 64;
            state = Closing;
        }
    }
    else if(state == Closing){
        animation_count = animation_count - 1;
        if(animation_count < 0){
            animation_count = 0;
            Engine::GameEngine::GetInstance().ChangeScene("start");
        }
    } */
}

void Door::Draw() const {
    //int offset = 267 * (animation_count / (64/6));
    int frame = animation_count / (64 / 6);
    if (frame > 5) frame = 5;
    int offset = frame * 267;

    ALLEGRO_BITMAP* bmp = this->bmp.get();

    if (!bmp) return;

    al_draw_tinted_scaled_bitmap(
        bmp, al_map_rgb(255, 255, 255),
            offset, 0, 267, 420, // source image x, y, width, height
            x, y, 267, 420, // destiny x, y, width, height
            0 // Flip or not
    );
}



void Door::PlayerEnterDoor() {
    if (state == Closed) {
        state = Opening;
        animation_count = 0;
    }
}