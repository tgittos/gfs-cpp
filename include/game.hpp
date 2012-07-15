#ifndef GAME_H
#define GAME_H

#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include <cassert>
#include "gameobjectmanager.hpp"
#include "gui.hpp"

class Game
{

public:
  const static int SCREEN_WIDTH = 1024;
  const static int SCREEN_HEIGHT = 768;

  static void Start();
  static sf::RenderWindow& GetWindow();
  const static sf::Input& GetInput();
  static GameObjectManager& GetGameObjectManager();

private:
  enum GameState {
    Uninitialized,
    ShowingSplash,
    Paused,
    ShowingMenu,
    Playing,
    Exiting
  };

  static GameState _gameState;
  static sf::RenderWindow _mainWindow;
  static GameObjectManager _gameObjectManager;
  static GUI _gui;

  static bool IsExiting();
  static void GameLoop();
  static void ShowSplashScreen();
  static void ShowMenu();

};

#endif
