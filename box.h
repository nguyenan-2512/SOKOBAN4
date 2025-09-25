#pragma once
#include "GameObject.h"

class Box : public GameObject {
private:
    Animation idleAnimation;
    Animation pushAnimation;
    bool isPushing;

public:
    Box(int x, int y, int tileSize);
    ~Box();

    bool loadAnimations();
    void draw(sf::RenderWindow& window) override;
    void update() override;

    void startPush();
    void stopPush();
};