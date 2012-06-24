#include "SplashScreen.hpp"
void SplashScreen::Show(sf::RenderWindow& window)
{
  char path[] = "assets/splash-screen.png";
  sf::Image image;
  if(!image.LoadFromFile(path))
  {
    return;
  }

  sf::Sprite sprite(image);

  window.Draw(sprite);
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
