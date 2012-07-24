#include "SplashScreen.hpp"
#include "game.hpp"
void SplashScreen::Show(sf::RenderWindow& window)
{
  window.Clear(sf::Color(0,0,0));

  char path[] = "assets/visitor.ttf";
  sf::Font font;
  if (!font.LoadFromFile(path))
  {
    return;
  }

  sf::String title = sf::String("Pang!", font, 72.f);
  title.SetPosition(
    Game::SCREEN_WIDTH / 2 - 100,
    Game::SCREEN_HEIGHT / 2 - 72
  );
  window.Draw(title);

  sf::String inst = sf::String("Click or press any key to continue", font, 24.f);
  inst.SetPosition(
    Game::SCREEN_WIDTH / 2 - 240,
    Game::SCREEN_HEIGHT / 2 + 15
  );
  window.Draw(inst);

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
