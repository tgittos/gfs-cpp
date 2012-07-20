#ifndef GAME_H
#define GAME_H

#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include <cassert>
#include "gameobjectmanager.hpp"
#include "gui.hpp"
#include "gameendscreen.hpp"

class Game
{

public:
  const static int SCREEN_WIDTH = 1024;
  const static int SCREEN_HEIGHT = 768;
  const static int WINNING_SCORE = 12;

  static void Start();
  static sf::RenderWindow& GetWindow();
  const static sf::Input& GetInput();
  static GameObjectManager& GetGameObjectManager();
  const static sf::Rect<int> GetGameField();

  static void Player1Scored();
  static void AIScored();
  static int* GetScore();

private:
  enum GameState {
    Uninitialized,
    ShowingSplash,
    Paused,
    ShowingMenu,
    Playing,
    GameOver,
    Exiting
  };

  static GameState _gameState;
  static sf::RenderWindow _mainWindow;
  static GameObjectManager _gameObjectManager;
  static GUI _gui;
  static sf::Rect<int> _gameField;
  static int _scores[2];

  static bool IsExiting();
  static void GameLoop();
  static void ShowSplashScreen();
  static void ShowMenu();
  static void ShowGameOverScreen();
  static void ResetGame();
};

#endif
