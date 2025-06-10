#include "Player/Player.hpp"
#include "Engine/Sprite.hpp"
#include "Scene/Playscene.hpp"
#include "Engine/GameEngine.hpp"
#include "Engine/Group.hpp"
#include "Engine/IScene.hpp"
#include <algorithm>

/* PlayScene *Player::getPlayScene() {
    return dynamic_cast<PlayScene *>(Engine::GameEngine::GetInstance().GetActiveScene());
}

Player::Player(std::string img, float x, float y, float w, float h) : Engine::Sprite(img, x, y, w, h, 0.5, 0), velocityY(0), onGround(true), playScene(getPlayScene()) {}
void Player::Update(float deltaTime) {
   
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
 */

int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
int h = Engine::GameEngine::GetInstance().GetScreenSize().y;

PlayScene* Player::getPlayScene() {
    return dynamic_cast<PlayScene*>(Engine::GameEngine::GetInstance().GetActiveScene());
}

Player::Player(std::string img, float x, float y, float w, float h)
    : Engine::Sprite(img, x, y, w, h, 0.5, 0), velocityY(0), onGround(true), playScene(getPlayScene()),
      isMovingLeft(false), isMovingRight(false), moveSpeed(200), gravity(1000), jumpSpeed(400) {
        floors = &(playScene->floors); // 把地板資料指標存起來
      }

bool IsColliding(float ax, float ay, float aw, float ah,
                 float bx, float by, float bw, float bh) {
    return ax < bx + bw && ax + aw > bx &&
           ay < by + bh && ay + ah > by;
}

/* void Player::Update(float deltaTime) {
    // 根據按鍵改變水平位置
    float dx = 0;
    if (isMovingLeft)
        dx -= moveSpeed * deltaTime;
    if (isMovingRight)
        dx += moveSpeed * deltaTime;

    // 應用水平移動
    Position.x += dx;

    // 重力效果
    velocityY += gravity * deltaTime;
    Position.y += velocityY * deltaTime;

    // 簡單地面檢查（假設地面為 y = 500）
    if (Position.y + Size.y >= 600) {
        Position.y = 600 - Size.y;
        velocityY = 0;
        onGround = true;
    } else {
        onGround = false;
    }

    Sprite::Update(deltaTime);
} */

void Player::Update(float deltaTime) {
    float oldX = Position.x;
    float oldY = Position.y;

    // 橫向移動
    float dx = 0;
    if (isMovingLeft) dx -= moveSpeed * deltaTime;
    if (isMovingRight) dx += moveSpeed * deltaTime;
    Position.x += dx;

    // ⛔ 檢查橫向碰撞
    for (auto& f : *floors) {
        if (IsColliding(Position.x, Position.y, Size.x, Size.y,
                        f.x, f.y, f.w, f.h)) {
            // 從右撞牆
            if (dx > 0) Position.x = f.x - Size.x;
            // 從左撞牆
            else if (dx < 0) Position.x = f.x + f.w;
        }
    }

    // 垂直移動
    velocityY += gravity * deltaTime;
    Position.y += velocityY * deltaTime;

    // ⛔ 檢查垂直碰撞
    onGround = false;
    for (auto& f : *floors) {
        if (IsColliding(Position.x, Position.y, Size.x, Size.y,
                        f.x, f.y, f.w, f.h)) {
            // 落地
            if (velocityY > 0) {
                Position.y = f.y - Size.y;
                velocityY = 0;
                onGround = true;
            }
            // 頭撞天花板
            else if (velocityY < 0) {
                Position.y = f.y + f.h;
                velocityY = 0;
            }
        }
    }

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
