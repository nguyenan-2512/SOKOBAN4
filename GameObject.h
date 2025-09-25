#pragma once
#include "Point.h"
#include "Animation.h"
#include <SFML/Graphics.hpp>

class GameObject {
protected:
    Point position;
    sf::Sprite sprite;
    int tileSize;
    Animation* currentAnimation;
    sf::Clock animationClock;
    bool hasAnimation;
public:
    GameObject(int x, int y, int tileSize);
    virtual ~GameObject() = default;
    Point getPosition() const;
    int getX() const;
    int getY() const;
    void setPosition(int x, int y);
    void setTexture(const sf::Texture& texture);
    void setAnimation(Animation* animation);
    void updateAnimation();
    virtual void draw(sf::RenderWindow& window) = 0;
    virtual void update();
};