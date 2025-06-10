#include "Player/Player.hpp"
#include "Engine/Sprite.hpp"
#include "Scene/PlayScene.hpp"
#include "Engine/GameEngine.hpp"
#include "Engine/Group.hpp"
#include "Engine/IScene.hpp"

PlayScene *Player::getPlayScene() {
    return dynamic_cast<PlayScene *>(Engine::GameEngine::GetInstance().GetActiveScene());
}

Player::Player(std::string img, float x, float y, float w, float h) : Engine::Sprite(img, x, y, w, h, 0.5, 0), velocityY(0), onGround(true), playScene(getPlayScene()) {}
void Player::Update(float deltaTime) {
    int gridX = static_cast<int>(x / PlayScene::BlockSize);
    int gridY = static_cast<int>(y / PlayScene::BlockSize);

    if (isMovingLeft && playScene->mapState[gridY][gridX] != PlayScene::TILE_DIRT && gridX > 0) {
        x -= moveSpeed * deltaTime;
    }
    else if (isMovingRight && playScene->mapState[gridY][gridX] != PlayScene::TILE_DIRT && gridX < PlayScene::MapWidth) {
        x += moveSpeed * deltaTime;
    }

    velocityY += gravity * deltaTime;
    y += velocityY * deltaTime;

    gridX = static_cast<int>(x / PlayScene::BlockSize);
    gridY = static_cast<int>((y + h - 1) / PlayScene::BlockSize);

    if (gridY >= 0 && gridY < PlayScene::MapHeight &&
        playScene->mapState[gridY + 1][gridX] == PlayScene::TILE_DIRT) {
        onGround = true;
        velocityY = 0;
        y = gridY * PlayScene::BlockSize - h +1;
    } else {
        onGround = false;
    }

    Position.x = x;
    Position.y = y;
}
void Player::Draw() const {
    Sprite::Draw();
}
void Player::Jump() {
    if (onGround) {
        velocityY = jumpSpeed;
        onGround = false;
    } 
}
