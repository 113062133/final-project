#ifndef PLAYER_HPP
#define PLAYER_HPP

class PlayScene;

class Player {
public:
    Player(PlayScene *scene,float x,float y);
    void Update(float deltaTime);
    void Draw() const;
    void Move(int dx,int dy);
private:
    float x,y;
    PlayScene *playScene;
};

#endif