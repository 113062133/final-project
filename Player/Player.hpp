#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Engine/Point.hpp"
#include "Engine/Sprite.hpp"
#include <vector>
#include <memory>

class PlayScene;

class Player : public Engine::Sprite {
public:
    Player(std::string img ,float x, float y, float w, float h);
    bool isMovingLeft, isMovingRight;
    bool onGround;
    void Update(float deltaTime);
    void Draw() const;
    void Jump();
    bool IsColliding(float ax, float ay, float aw, float ah,
                 float bx, float by, float bw, float bh);
private:
    // 全部原始幀貼圖
    std::vector<std::shared_ptr<ALLEGRO_BITMAP>> frames;

    // 兩組幀序列索引 (0-based)
    std::vector<int> seqRight = {0,1,2,1};
    std::vector<int> seqLeft  = {0,3,4,3};

    int seqPos = 0;            // 當前在序列中的位置
    float frameTimer = 0.0f;   // 計時器
    const float frameDelay = 0.1f;

    float x, y, w, h;
    float velocityY;
    const float moveSpeed = 300.0f;
    const float gravity = 1600.0f;
    const float jumpSpeed = -700.0f;
    
    PlayScene *playScene;
    PlayScene *getPlayScene();
};

#endif   // PLAYER_HPP