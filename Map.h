#pragma once
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include "Wall.h"
#include "Player.h"
#include "Floor.h"
#include "Box.h"

class Map {
private:
    std::vector<Wall> walls;
    std::vector<Floor> floors;
    std::vector<Box> boxes;
    Player* player;
    int tileSize;
    sf::Texture wallTexture;
    sf::Texture playerTexture;
    sf::Texture floorTexture;
    sf::Texture boxTexture;

public:
    Map(const std::string& filename, int tileSize = 32);
    ~Map();

    void update(); // NEW: Update all game objects
    void draw(sf::RenderWindow& window);
    Player* getPlayer();
};