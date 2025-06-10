#ifndef DOOR_HPP
#define DOOR_HPP


#include "Engine/Point.hpp"
#include "Engine/Sprite.hpp"

class PlayScene;

class Door : public Engine::Sprite {
public:
    enum DoorState { Closed, Opening};
    Door(std::string img, float x, float y, float w, float h);
    float offset;
    float animation_count;
    DoorState state;
    void Update(float deltaTime);
    void Draw() const;
    //void Move(int dx, int dy);
private:
    float x, y, w, h;
    bool entered;
    void PlayerEnterDoor();
    //PlayScene *playScene;
    //PlayScene *getPlayScene();
};

#endif   // Door_HPP