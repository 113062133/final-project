#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Engine/Point.hpp"
#include "Engine/Sprite.hpp"
#include <vector>
#include "Scene/Playscene.hpp"

class PlayScene;

class Player : public Engine::Sprite {
public:
    Player(std::string img, float x, float y, float w, float h);
    bool isMovingLeft, isMovingRight;
    bool onGround;
    void Update(float deltaTime);
    void Draw() const;
    void Jump();
    bool IsColliding(float ax, float ay, float aw, float ah,
                 float bx, float by, float bw, float bh);
private:
    float x, y, w, h;
    std::vector<Floor>* floors;
    float velocityY;
    const float moveSpeed = 200.0f;
    const float gravity = 1500.0f;
    const float jumpSpeed = -600.0f;
    
    PlayScene *playScene;
    PlayScene *getPlayScene();
};

#endif   // PLAYER_HPP