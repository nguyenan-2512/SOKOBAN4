#include "Player.h"
#include <iostream>

Player::Player(int x, int y, int tileSize) : GameObject(x, y, tileSize),
currentDirection(PlayerDirection::IDLE), isMoving(false) {
    loadAnimations();
}

Player::~Player() {
}

bool Player::loadAnimations() {
    // Load idle animation
    if (!idleAnimation.loadSpriteSheet("images/player_idle.png")) {
        std::cerr << "Failed to load player idle animation" << std::endl;
        return false;
    }
    idleAnimation.addFrame(0, 0, 60, 60); // 1 frame cho idle
    idleAnimation.setFrameTime(1.0f);
    idleAnimation.setLoop(true);

    // Load walk animations - 4 hướng
    if (!walkDownAnimation.loadSpriteSheet("images/player_walk_down.png")) {
        std::cerr << "Failed to load player walk down animation" << std::endl;
        return false;
    }
    walkDownAnimation.addFrameRow(0, 0, 60, 60, 4); // 4 frames
    walkDownAnimation.setFrameTime(0.15f); // Tăng tốc độ animation
    walkDownAnimation.setLoop(true);

    if (!walkUpAnimation.loadSpriteSheet("images/player_walk_up.png")) {
        std::cerr << "Failed to load player walk up animation" << std::endl;
        return false;
    }
    walkUpAnimation.addFrameRow(0, 0, 60, 60, 4);
    walkUpAnimation.setFrameTime(0.15f);
    walkUpAnimation.setLoop(true);

    if (!walkLeftAnimation.loadSpriteSheet("images/player_walk_left.png")) {
        std::cerr << "Failed to load player walk left animation" << std::endl;
        return false;
    }
    walkLeftAnimation.addFrameRow(0, 0, 60, 60, 4);
    walkLeftAnimation.setFrameTime(0.15f);
    walkLeftAnimation.setLoop(true);

    if (!walkRightAnimation.loadSpriteSheet("images/player_walk_right.png")) {
        std::cerr << "Failed to load player walk right animation" << std::endl;
        return false;
    }
    walkRightAnimation.addFrameRow(0, 0, 60, 60, 4);
    walkRightAnimation.setFrameTime(0.15f);
    walkRightAnimation.setLoop(true);

    // Bắt đầu với idle animation
    setAnimation(&idleAnimation);
    return true;
}

void Player::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}

void Player::update() {
    GameObject::update(); // Cập nhật animation

    // Nếu không đang di chuyển, chuyển về idle sau một khoảng thời gian
    static sf::Clock idleTimer;
    if (isMoving && idleTimer.getElapsedTime().asSeconds() > 0.3f) {
        setMoving(false);
        idleTimer.restart();
    }
}

void Player::move(int dx, int dy) {
    // Di chuyển vị trí
    setPosition(getX() + dx, getY() + dy);

    // Xác định hướng và set animation
    if (dx > 0) {
        setDirection(PlayerDirection::RIGHT);
    }
    else if (dx < 0) {
        setDirection(PlayerDirection::LEFT);
    }
    else if (dy > 0) {
        setDirection(PlayerDirection::DOWN);
    }
    else if (dy < 0) {
        setDirection(PlayerDirection::UP);
    }

    setMoving(true);
}

void Player::setDirection(PlayerDirection direction) {
    if (currentDirection == direction && isMoving) return;

    currentDirection = direction;

    // Chọn animation dựa trên hướng
    switch (direction) {
    case PlayerDirection::IDLE:
        setAnimation(&idleAnimation);
        break;
    case PlayerDirection::UP:
        setAnimation(&walkUpAnimation);
        break;
    case PlayerDirection::DOWN:
        setAnimation(&walkDownAnimation);
        break;
    case PlayerDirection::LEFT:
        setAnimation(&walkLeftAnimation);
        break;
    case PlayerDirection::RIGHT:
        setAnimation(&walkRightAnimation);
        break;
    }
}

void Player::setMoving(bool moving) {
    isMoving = moving;
    if (!moving) {
        setDirection(PlayerDirection::IDLE);
    }
}

// Thêm method để kiểm tra trạng thái
bool Player::getIsMoving() const {
    return isMoving;
}

PlayerDirection Player::getCurrentDirection() const {
    return currentDirection;
}