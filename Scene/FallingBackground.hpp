#pragma once
#include "Engine/Sprite.hpp"

class FallingBackground : public Engine::Sprite {
public:
    float fallSpeed;
    bool isFalling;

    FallingBackground(std::string img, float speed);
    void Start();
    void Update(float deltaTime) override;
};
