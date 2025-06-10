#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Engine/Point.hpp"
#include "Engine/Sprite.hpp"

class PlayScene;

class Player : public Engine::Sprite {
public:
    Player(std::string img, float x, float y, float w, float h);
    void Update(float deltaTime);
    void Draw() const;
    void Move(int dx, int dy);
private:
    float x, y, w, h;
    float velocityY;
    bool onGround;
    const float gravity = 1000.0f;
    const float jumpSpeed = -600.0f;
    
    PlayScene *playScene;
    PlayScene *getPlayScene();
};

#endif   // PLAYER_HPP