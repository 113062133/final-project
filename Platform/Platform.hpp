#ifndef PLATFORM_HPP
#define PLATFORM_HPP

class PlayScene;

class Platform {
public:
    Platform(PlayScene *scene,float x,float y);
    void Update(float deltaTime);
    void Draw() const;
private:
    float x,y,w,h;
    PlayScene *playScene;
};

#endif