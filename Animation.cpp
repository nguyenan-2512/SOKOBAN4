#include "Animation.h"
#include <iostream>

Animation::Animation() : currentFrame(0), frameTime(0.1f), elapsedTime(0.0f),
isPlaying(false), isLooping(true) {
}

Animation::~Animation() {
}

bool Animation::loadSpriteSheet(const std::string& filename) {
    if (!spriteSheet.loadFromFile(filename)) {
        std::cerr << "Failed to load spritesheet: " << filename << std::endl;
        return false;
    }
    return true;
}

void Animation::addFrame(int x, int y, int width, int height) {
    frames.push_back(sf::IntRect(x, y, width, height));
}

void Animation::addFrameRow(int startX, int startY, int frameWidth, int frameHeight, int frameCount) {
    for (int i = 0; i < frameCount; i++) {
        addFrame(startX + (i * frameWidth), startY, frameWidth, frameHeight);
    }
}

void Animation::play() {
    isPlaying = true;
}

void Animation::pause() {
    isPlaying = false;
}

void Animation::stop() {
    isPlaying = false;
    currentFrame = 0;
    elapsedTime = 0.0f;
}

void Animation::setLoop(bool loop) {
    isLooping = loop;
}

void Animation::setFrameTime(float time) {
    frameTime = time;
}

void Animation::update(float deltaTime) {
    if (!isPlaying || frames.empty()) return;

    elapsedTime += deltaTime;

    if (elapsedTime >= frameTime) {
        elapsedTime = 0.0f;
        currentFrame++;

        if (currentFrame >= frames.size()) {
            if (isLooping) {
                currentFrame = 0;
            }
            else {
                currentFrame = frames.size() - 1;
                isPlaying = false;
            }
        }
    }
}

sf::IntRect Animation::getCurrentFrame() const {
    if (frames.empty()) return sf::IntRect();
    return frames[currentFrame];
}

sf::Texture& Animation::getTexture() {
    return spriteSheet;
}

bool Animation::isAnimationPlaying() const {
    return isPlaying;
}

bool Animation::isAnimationFinished() const {
    return !isLooping && currentFrame >= frames.size() - 1 && !isPlaying;
}