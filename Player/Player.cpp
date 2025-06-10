#include "Player.hpp"
#include "Engine/Sprite.hpp"
#include "Scene/PlayScene.hpp"
#include "Engine/GameEngine.hpp"
#include "Engine/Group.hpp"
#include "Engine/IScene.hpp"

PlayScene *Player::getPlayScene() {
    return dynamic_cast<PlayScene *>(Engine::GameEngine::GetInstance().GetActiveScene());
}

Player::Player(std::string img, float x, float y) : Engine::Sprite(img, x, y), x(x), y(y), 
                                                    velocityY(0), onGround(true), playScene(getPlayScene()) {}
void Player::Update(float deltaTime) {
    velocityY += gravity * deltaTime;
    y += velocityY * deltaTime;

    int gridX = static_cast<int>(x / PlayScene::BlockSize);
    int gridY = static_cast<int>((y + PlayScene::BlockSize - 1) / PlayScene::BlockSize);

    if (gridY >= 0 && gridY < PlayScene::MapHeight &&
        playScene->mapState[gridY][gridX] == PlayScene::TILE_DIRT) {
        onGround = true;
        velocityY = 0;
        y = gridY * PlayScene::BlockSize;
    } else {
        onGround = false;
    }

    Position.x = x;
    Position.y = y;
}
void Player::Draw() const {
    Sprite::Draw();
}
void Player::Move(int dx, int dy) {
    x += dx *PlayScene::BlockSize;
    if (dy == -1 && onGround) {
        velocityY = jumpSpeed;
        onGround = false;
    } 
}
