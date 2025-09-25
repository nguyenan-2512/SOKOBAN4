#pragma once
#include <SFML/Graphics.hpp>
#include "Menu.h"
#include "Map.h"

enum class GameState {
    MENU,
    PLAYING,
    PAUSED,
    GAME_OVER
};

class Game {
private:
    sf::RenderWindow window;
    Menu menu;
    Map* currentMap;
    GameState gameState;

public:
    Game();
    ~Game();
    void run();

private:
    void handleEvents();
    void update();
    void render();
    void initializeGame();
    void cleanupGame();
};