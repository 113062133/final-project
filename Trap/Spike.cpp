#include "Trap/Spike.hpp"
#include "Engine/Sprite.hpp"
#include "Scene/Playscene.hpp"
#include "Engine/GameEngine.hpp"
#include "Engine/Group.hpp"
#include "Engine/IScene.hpp"


Spike::Spike(std::string img, float x, float y, float w, float h) : Engine::Sprite(img, x, y, w, h, 0.5, 1), x(x), y(y), w(w), h(h)
                                              {}
void Spike::Update(float deltaTime) {

}
void Spike::Draw() const {
    Sprite::Draw();
}
void Spike::Move(int dx, int dy) {
    
}