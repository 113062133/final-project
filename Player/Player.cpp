#include "Player.hpp"

Player::Player(float startX, float startY) {
    x = startX;
    y = startY;
    vx = vy = 0;
    width = 32;
    height = 48;
    onGround = false;
    wantToJump = false;

    sprite = al_load_bitmap("images/player.png");
    if (!sprite) {
        // 若沒圖片可 fallback 畫方塊
        sprite = nullptr;
    }
}

Player::~Player() {
    if (sprite) {
        al_destroy_bitmap(sprite);
    }
}

void Player::handle_input(bool left, bool right, bool jump) {
    vx = 0;
    if (left) vx -= MOVE_SPEED;
    if (right) vx += MOVE_SPEED;
    if (jump && onGround) {
        wantToJump = true;
    }
}

void Player::update(float dt) {
    if (wantToJump && onGround) {
        vy = JUMP_SPEED;
        onGround = false;
        wantToJump = false;
    }

    // Apply gravity
    vy += GRAVITY * dt;

    // Update position
    x += vx * dt;
    y += vy * dt;

    // 假設地面是 y = 500
    if (y + height >= 500) {
        y = 500 - height;
        vy = 0;
        onGround = true;
    }
}

void Player::draw() {
    if (sprite) {
        al_draw_bitmap(sprite, x, y, 0);
    } else {
        al_draw_filled_rectangle(x, y, x + width, y + height, al_map_rgb(255, 0, 0));
    }
}

void Player::set_on_ground(bool value) {
    onGround = value;
}

bool Player::is_on_ground() const {
    return onGround;
}

float Player::get_x() const {
    return x;
}

float Player::get_y() const {
    return y;
}
