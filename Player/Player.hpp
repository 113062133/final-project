#ifndef PLAYER_H
#define PLAYER_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h> // 如你用畫方塊
#include <allegro5/allegro_image.h>
#include "Scene/Playscene.hpp"      // 如你用圖片

class Player {
public:
    Player(float startX, float startY);
    ~Player();

    void update(float deltaTime);
    void draw();
    void handle_input(bool left, bool right, bool jump);

    void set_on_ground(bool value);
    bool is_on_ground() const;

    float get_x() const;
    float get_y() const;

private:
    float x, y;
    float vx, vy;
    float width, height;

    bool onGround;
    bool wantToJump;

    const float MOVE_SPEED = 200.0f;
    const float JUMP_SPEED = -400.0f;
    const float GRAVITY = 800.0f;

    ALLEGRO_BITMAP* sprite;
};

#endif
