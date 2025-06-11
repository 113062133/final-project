#include "FallingBackground.hpp"
#include "Engine/GameEngine.hpp"

FallingBackground::FallingBackground(std::string img, float speed) :
    Engine::Sprite(img, 0, -Engine::GameEngine::GetInstance().GetScreenSize().y),
    fallSpeed(speed), isFalling(false) {}

void FallingBackground::Start() {
    isFalling = true;
}

void FallingBackground::Update(float deltaTime) {
    if (isFalling) {
        Position.y += fallSpeed * deltaTime;
        if (Position.y >= 0) {
            Position.y = 0;
            isFalling = false;
        }
    }
    Engine::Sprite::Update(deltaTime);
}
