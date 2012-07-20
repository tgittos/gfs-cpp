#include <sstream>
#include "gui.hpp"
#include "game.hpp"

GUI::GUI()
{
  // 'new' places is on the heap, which means we need
  // to count references and delete it when we're
  // done.
  _font = new sf::Font();
  if (!_font->LoadFromFile("assets/visitor.ttf"))
  {
    // handle the error
  }
}

GUI::~GUI()
{
  delete _font;
}

void GUI::Draw(sf::RenderWindow& window)
{
  int* scores = Game::GetScore();
  
  std::ostringstream player1out;
  player1out << "Player: " << scores[0];
  
  std::ostringstream aiout;
  aiout << "Computer: " << scores[1];
  
  // dereference the pointer to get the actual object
  sf::String player1(player1out.str(), *_font);
  sf::String ai(aiout.str(), *_font);
  sf::String ident("Pang!", *_font);
  
  player1.SetX(10);
  ident.SetX(Game::SCREEN_WIDTH / 2 - 50);
  ai.SetX(Game::SCREEN_WIDTH - 200);
  
  window.Draw(player1);
  window.Draw(ident);
  window.Draw(ai);

  sf::Rect<int> gameField = Game::GetGameField();
  window.Draw(sf::Shape::Line(
    gameField.Left, gameField.Top,
    gameField.Right, gameField.Top,
    2, sf::Color::White
  ));
  window.Draw(sf::Shape::Line(
    gameField.Left, gameField.Bottom,
    gameField.Right, gameField.Bottom,
    2, sf::Color::White
  ));
}
