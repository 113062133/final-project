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
