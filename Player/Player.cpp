/* #include "Player/Player.hpp"
#include "Engine/Sprite.hpp"
#include "Scene/Playscene.hpp"
#include "Engine/GameEngine.hpp"
#include "Engine/Group.hpp"
#include "Engine/IScene.hpp"
#include <algorithm>
#include "Scene/FallingBackground.hpp" */

#include "Engine/AudioHelper.hpp"
#include "Engine/GameEngine.hpp"
#include "Engine/Group.hpp"
#include "Engine/LOG.hpp"
#include "Engine/Point.hpp"
#include "Engine/IObject.hpp"
#include "Engine/Resources.hpp"
#include "Scene/Playscene.hpp"
#include "Scene/WinScene.hpp"
#include "Trap/Spike.hpp"
#include "UI/Component/Image.hpp"
#include "UI/Component/ImageButton.hpp"
#include "UI/Component/Label.hpp"
#include "allegro5/keycodes.h"
#include "Door/Door.hpp"
#include "Player/Player.hpp"
#include "Scene/FallingBackground.hpp"
#include "Scene/Playscene.hpp"
#include "allegro5/allegro_primitives.h"


//int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
//int h = Engine::GameEngine::GetInstance().GetScreenSize().y;

PlayScene* Player::getPlayScene() {
    return dynamic_cast<PlayScene*>(Engine::GameEngine::GetInstance().GetActiveScene());
}

Player::Player(std::string img, float x, float y, float w, float h)
    : Engine::Sprite(img, x, y, w, h, 0, 0), velocityY(0), onGround(true), playScene(getPlayScene()),
      isMovingLeft(false), isMovingRight(false), moveSpeed(200), gravity(1000), jumpSpeed(400) {
        // 把地板資料指標存起來
      }

bool Player::IsColliding(float ax, float ay, float aw, float ah,
                 float bx, float by, float bw, float bh) {
    return ax < bx + bw && ax + aw > bx && 
           ay < by + bh && ay + ah > by;
}

void Player::Update(float deltaTime) {
    // 檢查透明方塊碰撞
    for (auto& block : playScene->triggerBlocks) {
        if (IsColliding(Position.x, Position.y, Size.x, Size.y,
                        block.x, block.y, block.w, block.h)) {
            if (block.target && !block.target->activated) {
                block.target->activated = true;
                if(block.target->type == PlayScene::ObjectType::SPIKE_FLOOR){
                    playScene->objects.push_back({block.target->x, block.target->y - 20, block.target->w, 20, 0, 0,0,0, PlayScene::ObjectType::SPIKE, false});
                    playScene->TileMapGroup->AddNewObject(new Engine::Image("play/spike1.png", block.target->x, block.target->y - 20, block.target->w, 20));
                }
                else if(block.target->type == PlayScene::ObjectType::PORTAL){
                    Position.x = block.target->w;
                    Position.y = block.target->h;
                }            
                else if(block.target->type == PlayScene::ObjectType::FAKE_DOOR){
                    playScene->objects.push_back({block.target->x, block.target->y - 20, block.target->w, 20, 0, 0,0, PlayScene::ObjectType::SPIKE});
                    playScene->TileMapGroup->AddNewObject(new Engine::Image("play/spike1.png", block.target->x, block.target->y + 30, block.target->w, 20));
                }
                else if(block.target->type == PlayScene::ObjectType::FAKE_WALL){
                    playScene->objects.push_back({block.target->x, block.target->y - 20, block.target->w, 20, 0, 0,0, PlayScene::ObjectType::DOOR});
                    playScene->TileMapGroup->AddNewObject(new Engine::Image("play/door.png", block.target->x, block.target->y +50 , block.target->w, 50));
                }
            }
        }
    }
    float oldX = Position.x;
    float oldY = Position.y;

    // 橫向移動
    float dx = 0;
    if (isMovingLeft) dx -= moveSpeed * deltaTime;
    if (isMovingRight) dx += moveSpeed * deltaTime;
    Position.x += dx;
    

    
    // 檢查橫向碰撞
    for (const auto& obj : playScene->objects) {
        if (IsColliding(Position.x, Position.y, Size.x, Size.y,
                        obj.x, obj.y, obj.w, obj.h)) {
            if (obj.type == PlayScene::ObjectType::FLOOR ) {
                // 地板：阻止穿透
                if (dx > 0) Position.x = obj.x - Size.x; // 從右撞牆
                else if (dx < 0) Position.x = obj.x + obj.w; // 從左撞牆
            }
            else if(obj.type == PlayScene::ObjectType::PUSH_FLOOR){
                
                if(obj.activated)
                    Position.x += obj.speedx * deltaTime;
                if (dx > 0) Position.x = obj.x - Size.x; // 從右撞牆
                else if (dx < 0) Position.x = obj.x + obj.w; // 從左撞牆
            }
            else if (obj.type == PlayScene::ObjectType::DOOR||obj.type == PlayScene::ObjectType::FAKE_WALL) {
                // 門：切換場景（示例）
                if(playScene -> flag == 0){
                    auto falling = new Engine::Image("stage-select/background2.png", 0, -832, 1600, 832);
                    playScene -> fallingBG = falling;
                    playScene->AddNewObject(falling);
                    playScene -> flag = 1;
                }
            } else if (obj.type == PlayScene::ObjectType::SPIKE) {
                Engine::GameEngine::GetInstance().ChangeScene("play");
            } else if (obj.type == PlayScene::ObjectType::SPIKE_FLOOR && obj.activated) {
                Engine::GameEngine::GetInstance().ChangeScene("play");
            } else if (obj.type == PlayScene::ObjectType::BOUNCE) {
                if (onGround) {
                    velocityY = -1500;
                    onGround = false;
                }
            }
        }
    }

    // 垂直移動
    velocityY += gravity * deltaTime;
    Position.y += velocityY * deltaTime;
    if (Position.y > Engine::GameEngine::GetInstance().GetScreenSize().y + 100) {
        Engine::GameEngine::GetInstance().ChangeScene("play");
        return;
    }

    // ⛔ 檢查垂直碰撞
    onGround = false;
   for (const auto& obj : playScene->objects) {
        if (IsColliding(Position.x, Position.y, Size.x, Size.y,
                        obj.x, obj.y, obj.w, obj.h)) {
            if (obj.type == PlayScene::ObjectType::FLOOR ) {
                // 地板：處理地面和天花板
                if (velocityY > 0) { // 落地
                    Position.y = obj.y - Size.y;
                    velocityY = 0;
                    onGround = true;
                } else if (velocityY < 0) { // 頭撞天花板
                    Position.y = obj.y + obj.h;
                    velocityY = 0;
                }
            } 
            else if(obj.type == PlayScene::ObjectType::PUSH_FLOOR){
                // 地板：處理地面和天花板
                if (velocityY > 0) { // 落地
                    Position.y = obj.y - Size.y;
                    velocityY = 0;
                    onGround = true;
                } else if (velocityY < 0) { // 頭撞天花板
                    Position.y = obj.y + obj.h;
                    velocityY = 0;
                }
                if(obj.activated)
                    Position.x += obj.speedx * deltaTime;
            }
            else if (obj.type == PlayScene::ObjectType::DOOR) {
                if(playScene -> flag == 0){
                    auto falling = new Engine::Image("stage-select/background2.png", 0, -832, 1600, 832);
                    playScene -> fallingBG = falling;
                    playScene->AddNewObject(falling);
                    playScene -> flag = 1;
                }
            } else if (obj.type == PlayScene::ObjectType::SPIKE) {
                Engine::GameEngine::GetInstance().ChangeScene("play");
            } else if (obj.type == PlayScene::ObjectType::SPIKE_FLOOR && obj.activated) {
                
                Engine::GameEngine::GetInstance().ChangeScene("play");
            } else if (obj.type == PlayScene::ObjectType::BOUNCE) {
                if (onGround) {
                    velocityY = -1500;
                    onGround = false;
                }
            }
        }
    }
    //trigger
    /*for (auto& obj : playScene->objects) {
        if (obj.type == PlayScene::ObjectType::MOVING_FLOOR) {
            // 若玩家觸碰或非常接近，就啟動
            if (!obj.activated &&
                Position.x + Size.x > obj.x - 10 &&
                Position.x < obj.x + obj.w + 10) {
                obj.activated = true;
                obj.speedy = 500; // 每秒下墜 500 px，可自行調整
                break;
            }
        } else if (obj.type == PlayScene::ObjectType::SPIKE_FLOOR) {
            if (!obj.activated &&
                Position.x + Size.x > obj.x - 10 &&
                Position.x < obj.x + obj.w + 10) {
                obj.activated = true;
                playScene->objects.push_back({obj.x, obj.y - 20, obj.w, 20, 0, 0,0, PlayScene::ObjectType::SPIKE});
                playScene->TileMapGroup->AddNewObject(new Engine::Image("play/spike1.png", obj.x, obj.y - 20, obj.w, 20));
                break;
            }
        }
        else if (obj.type == PlayScene::ObjectType::PUSH_FLOOR) {
            // 若玩家觸碰或非常接近，就啟動
            if (!obj.activated &&
                Position.x + Size.x > obj.x - 30 &&
                Position.x < obj.x + obj.w + 30) {
                obj.activated = true;
                break;
            }
        }
    }*/

    Sprite::Update(deltaTime);
}


void Player::Draw() const {
    Sprite::Draw();
}

void Player::Jump() {
    if (onGround) {
        velocityY = -jumpSpeed;
        onGround = false;
    }
}
