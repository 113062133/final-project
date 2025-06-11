#ifndef DOOR_HPP
#define DOOR_HPP


#include "Engine/Point.hpp"
#include "Engine/Sprite.hpp"
#include <string>

/* class PlayScene;

class Door : public Engine::Sprite {
public:
    enum DoorState { Closed, Opening, Closing};
    Door(std::string img, float x, float y, float w, float h);
    float offset;
    float animation_count;
    DoorState state;
    void Update(float deltaTime);
    void Draw() const;
    int totalFrames;         // 門動畫總幀數
    int currentFrame;        // 當前幀
    float frameTime;         // 每幀持續時間
    float frameTimer;        // 幀累計時間
    int frameWidth;          // 每幀的寬度（從 spritesheet 切圖用）

private:
    float x, y, w, h;
    bool entered;
    void PlayerEnterDoor();
    //PlayScene *playScene;
    //PlayScene *getPlayScene();
}; */

class Door : public Engine::Sprite {
public:
    enum DoorState { Closed, Opening, Closing };
    Door(std::string img, float x, float y, float w, float h);
    float offset;
    float animation_count;
    DoorState state;
    void Update(float deltaTime);
    void Draw() const;
    void PlayerEnterDoor();
    int currentFrame = 0;
    float frameTimer = 0;

private:
    float x, y, w, h;
    bool entered;
    std::string img;

    static constexpr int frameCount = 6;
    static constexpr float frameDuration = 0.1f; // 每幀持續時間（秒）
};



#endif   // Door_HPP