#ifndef GAME_H

#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"

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

  static bool IsExiting();
  static void GameLoop();

};

#endif
