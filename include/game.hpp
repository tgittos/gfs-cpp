#ifndef GAME_H
#define GAME_H

#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "playerpaddle.hpp"

class Game
{

public:
  static void Start();

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
  static PlayerPaddle _player1;

  static bool IsExiting();
  static void GameLoop();
  static void ShowSplashScreen();
  static void ShowMenu();

};

#endif
