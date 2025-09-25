#pragma once
#include "GameObject.h"

enum class PlayerDirection {
    IDLE,
    UP,
    DOWN,
    LEFT,
    RIGHT
};

class Player : public GameObject {
private:
    // Animations cho từng hướng
    Animation idleAnimation;
    Animation walkUpAnimation;
    Animation walkDownAnimation;
    Animation walkLeftAnimation;
    Animation walkRightAnimation;

    PlayerDirection currentDirection;
    bool isMoving;

public:
    Player(int x = 0, int y = 0, int tileSize = 40);
    ~Player();

    // Load animations
    bool loadAnimations();

    void draw(sf::RenderWindow& window) override;
    void update() override;
    void move(int dx, int dy);

    // Set direction and animation
    void setDirection(PlayerDirection direction);
    void setMoving(bool moving);

    // Getter methods để kiểm tra trạng thái
    bool getIsMoving() const;
    PlayerDirection getCurrentDirection() const;
};