#include "gui.hpp"

GUI::GUI()
{
}

GUI::~GUI()
{
}

void GUI::Draw(sf::RenderWindow& window)
{
  // temp text testing stuff
  sf::String test("This is a test");
  window.Draw(test);
}
