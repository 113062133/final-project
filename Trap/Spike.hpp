#ifndef SPIKE_HPP
#define SPIKE_HPP

#include "Engine/Point.hpp"
#include "Engine/Sprite.hpp"

//class PlayScene;

class Spike : public Engine::Sprite {
public:
    Spike(std::string img, float x, float y, float w, float h);
    void Update(float deltaTime);
    void Draw() const;
    void Move(int dx, int dy);
private:
    float x, y, w, h;
    float velocityY;
    bool onGround;
    const float gravity = 1000.0f;
    const float jumpSpeed = -600.0f;

    /*PlayScene *playScene;
    PlayScene *getPlayScene();*/
};

#endif   // SPIKE_HPP