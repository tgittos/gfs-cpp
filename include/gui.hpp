#ifndef GUI_H
#define GUI_H

#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"

class GUI
{
public:
  GUI();
  ~GUI();

  void Draw(sf::RenderWindow& window);
private:
  sf::Font* _font;
};

#endif
