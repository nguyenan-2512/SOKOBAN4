#include "GameObject.h"

GameObject::GameObject(int x, int y, int tileSize) : position(x, y), tileSize(tileSize),
currentAnimation(nullptr), hasAnimation(false) {
    sprite.setPosition(static_cast<float>(x * tileSize), static_cast<float>(y * tileSize));
}

Point GameObject::getPosition() const {
    return position;
}

int GameObject::getX() const {
    return position.getX();
}

int GameObject::getY() const {
    return position.getY();
}

void GameObject::setPosition(int x, int y) {
    position.setXY(x, y);
    sprite.setPosition(static_cast<float>(x * tileSize), static_cast<float>(y * tileSize));
}

void GameObject::setTexture(const sf::Texture& texture) {
    sprite.setTexture(texture);
    hasAnimation = false;
}

void GameObject::setAnimation(Animation* animation) {
    currentAnimation = animation;
    hasAnimation = (animation != nullptr);
    if (hasAnimation) {
        sprite.setTexture(currentAnimation->getTexture());
        currentAnimation->play();
    }
}

void GameObject::updateAnimation() {
    if (hasAnimation && currentAnimation) {
        float deltaTime = animationClock.restart().asSeconds();
        currentAnimation->update(deltaTime);
        sprite.setTextureRect(currentAnimation->getCurrentFrame());
    }
}

void GameObject::update() {
    updateAnimation();
}