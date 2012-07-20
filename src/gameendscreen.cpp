#include "gameendscreen.hpp"
#include "game.hpp"

GameEndScreen::GameEndScreen()
{
  _font = new sf::Font();
  if (!_font->LoadFromFile("assets/visitor.ttf"))
  {
    // handle the error
  }
}

GameEndScreen::~GameEndScreen()
{
  delete _font;
}

void GameEndScreen::ShowWin(sf::RenderWindow& window)
{
  DrawBacking(window);
  sf::String msg = sf::String("You won", *_font, 72.f);
  msg.SetPosition(
    Game::SCREEN_WIDTH / 2 - 150,
    Game::SCREEN_HEIGHT / 2 - 100
  );
  window.Draw(msg);
  window.Display();

  sf::Event event;
  while(true)
  {
    while(window.GetEvent(event))
    {
      if(event.Type == sf::Event::KeyPressed ||
         event.Type == sf::Event::MouseButtonPressed ||
         event.Type == sf::Event::Closed)
      {
        return;
      }
    }
  }
}

void GameEndScreen::ShowLose(sf::RenderWindow& window)
{
  DrawBacking(window);
  sf::String msg = sf::String("You lost", *_font, 72.f);
  msg.SetPosition(
    Game::SCREEN_WIDTH / 2 - 160,
    Game::SCREEN_HEIGHT / 2 - 100
  );
  window.Draw(msg);
  window.Display();

  sf::Event event;
  while(true)
  {
    while(window.GetEvent(event))
    {
      if(event.Type == sf::Event::KeyPressed ||
         event.Type == sf::Event::MouseButtonPressed ||
         event.Type == sf::Event::Closed)
      {
        return;
      }
    }
  }
}

void GameEndScreen::DrawBacking(sf::RenderWindow& window)
{
  sf::Color transparentBlack = sf::Color(
    0, 0, 0, 255 * 0.75
  );
  window.Draw(sf::Shape::Rectangle(
    0, 0,
    Game::SCREEN_WIDTH, Game::SCREEN_HEIGHT,
    transparentBlack
  ));
}
