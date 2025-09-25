#include "Game.h"
#include <iostream>
using namespace std;

Game::Game() : window(sf::VideoMode(800, 600), "Sokoban"), currentMap(nullptr), gameState(GameState::MENU) {
    window.setFramerateLimit(60);
    menu.loadResources();
}

Game::~Game() {
    cleanupGame();
}

void Game::run() {
    while (window.isOpen()) {
        handleEvents();
        update();
        render();
    }
}

void Game::handleEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }

        if (gameState == GameState::MENU) {
            menu.handleEvent(event, window);
        }
        else if (gameState == GameState::PLAYING) {
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape) {
                    // Return to menu
                    gameState = GameState::MENU;
                    menu.setState(MenuState::MENU);
                    cleanupGame();
                }
                else if (currentMap && currentMap->getPlayer()) {
                    // Handle player movement
                    Player* player = currentMap->getPlayer();
                    if (event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::W) {
                        player->move(0, -1);
                    }
                    if (event.key.code == sf::Keyboard::Down || event.key.code == sf::Keyboard::S) {
                        player->move(0, 1);
                    }
                    if (event.key.code == sf::Keyboard::Left || event.key.code == sf::Keyboard::A) {
                        player->move(-1, 0);
                    }
                    if (event.key.code == sf::Keyboard::Right || event.key.code == sf::Keyboard::D) {
                        player->move(1, 0);
                    }
                }
            }
        }
    }
}

void Game::update() {
    if (gameState == GameState::MENU) {
        menu.update();

        MenuState menuState = menu.getState();
        if (menuState == MenuState::PLAYING) {
            gameState = GameState::PLAYING;
            initializeGame();
        }
        else if (menuState == MenuState::EXIT) {
            window.close();
        }
    }
    else if (gameState == GameState::PLAYING) {
        // UPDATE: Gọi update cho map và tất cả objects
        if (currentMap) {
            currentMap->update();
        }
    }
}

void Game::render() {
    window.clear();

    if (gameState == GameState::MENU) {
        menu.draw(window);
    }
    else if (gameState == GameState::PLAYING) {
        if (currentMap) {
            currentMap->draw(window);
        }
    }

    window.display();
}

void Game::initializeGame() {
    cleanupGame(); // Clean up any existing game
    currentMap = new Map("map1.txt", 32);
    cout << "Game initialized!" << endl;
}

void Game::cleanupGame() {
    if (currentMap) {
        delete currentMap;
        currentMap = nullptr;
    }
}