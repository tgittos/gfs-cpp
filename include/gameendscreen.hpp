#ifndef GAME_END_SCREEN_H
#define GAME_END_SCREEN_H

#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"

class GameEndScreen
{
public:
  GameEndScreen();
  ~GameEndScreen();

  void ShowWin(sf::RenderWindow& window);
  void ShowLose(sf::RenderWindow& window);

private:
  sf::Font* _font;

  void DrawBacking(sf::RenderWindow& window);
};

#endif
