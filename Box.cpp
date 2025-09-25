#include "Box.h"
#include <iostream>

Box::Box(int x, int y, int tileSize) : GameObject(x, y, tileSize), isPushing(false) {
    loadAnimations();
}

Box::~Box() {
}

bool Box::loadAnimations() {
    // Load idle animation for box
    if (!idleAnimation.loadSpriteSheet("images/box_idle.png")) {
        std::cerr << "Failed to load box idle animation" << std::endl;
        return false;
    }
    idleAnimation.addFrame(0, 0, 32, 32);
    idleAnimation.setFrameTime(0.5f);
    idleAnimation.setLoop(true);

    // Load push animation
    if (!pushAnimation.loadSpriteSheet("images/box_push.png")) {
        std::cerr << "Failed to load box push animation" << std::endl;
        return false;
    }
    pushAnimation.addFrameRow(0, 0, 32, 32, 3); // 3 frames shake effect
    pushAnimation.setFrameTime(0.1f);
    pushAnimation.setLoop(false);

    // Set initial animation
    setAnimation(&idleAnimation);
    return true;
}

void Box::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}

void Box::update() {
    GameObject::update();

    // Nếu push animation kết thúc, chuyển về idle
    if (isPushing && pushAnimation.isAnimationFinished()) {
        stopPush();
    }
}

void Box::startPush() {
    if (!isPushing) {
        isPushing = true;
        pushAnimation.stop(); // Reset animation
        setAnimation(&pushAnimation);
    }
}

void Box::stopPush() {
    isPushing = false;
    setAnimation(&idleAnimation);
}