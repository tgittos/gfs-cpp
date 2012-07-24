#include "mainmenu.hpp"
#include "servicelocator.hpp"
MainMenu::MainMenu()
{
  _font = new sf::Font();
  if (!_font->LoadFromFile("assets/visitor.ttf"))
  {
    // handle the error
  }
}
MainMenu::~MainMenu()
{
  delete _font;
}
MainMenu::MenuResult MainMenu::Show(sf::RenderWindow& window)
{
  MenuItem playButton;
  playButton.rect.Top = 768 / 2 - 100;
  playButton.rect.Bottom = 768 / 2 ;
  playButton.rect.Left = 1024 / 3;
  playButton.rect.Right = 1024 / 3 * 2;
  playButton.action = Play;

  MenuItem exitButton;
  exitButton.rect.Top = 768 / 2;
  exitButton.rect.Bottom = 768 / 2 + 100;
  exitButton.rect.Left = 1024 / 3;
  exitButton.rect.Right = 1024 / 3 * 2;
  exitButton.action = Exit;

  _menuItems.push_back(playButton);
  _menuItems.push_back(exitButton);

  window.Clear(sf::Color(0,0,0));

  sf::Shape playRect = sf::Shape::Rectangle(
    playButton.rect.Left * 1.f,
    playButton.rect.Top * 1.f,
    playButton.rect.Right * 1.f,
    playButton.rect.Bottom * 1.f,
    sf::Color::White, true, sf::Color::White
  );
  playRect.EnableFill(false);
  window.Draw(playRect);
  
  sf::Shape exitRect = sf::Shape::Rectangle(
    exitButton.rect.Left * 1.f,
    exitButton.rect.Top * 1.f,
    exitButton.rect.Right * 1.f,
    exitButton.rect.Bottom * 1.f,
    sf::Color::White, true, sf::Color::White
  );
  exitRect.EnableFill(false);
  window.Draw(exitRect);

  sf::String playLabel = sf::String("Start game", *_font);
  playLabel.SetPosition(1024 / 2 - 90, playButton.rect.Top + 30);
  window.Draw(playLabel);
  
  sf::String exitLabel = sf::String("Exit game", *_font);
  exitLabel.SetPosition(1024 / 2 - 75, exitButton.rect.Top + 30);
  window.Draw(exitLabel);

  window.Display();

  return GetMenuResponse(window);
}
MainMenu::MenuResult MainMenu::GetMenuResponse(sf::RenderWindow& window)
{
  sf::Event menuEvent;
  while(true)
  {
    while(window.GetEvent(menuEvent))
    {
      if (menuEvent.Type == sf::Event::MouseButtonPressed)
      {
        return HandleClick(menuEvent.MouseButton.X, menuEvent.MouseButton.Y);
      }
      if (menuEvent.Type == sf::Event::Closed)
      {
        return Exit;
      }
    }
  }
}

MainMenu::MenuResult MainMenu::HandleClick(int x, int y)
{
  std::list<MenuItem>::iterator it;
  for (it = _menuItems.begin(); it != _menuItems.end(); it++)
  {
    sf::Rect<int> menuItemRect = (*it).rect;
    if (menuItemRect.Bottom > y && menuItemRect.Top < y &&
        menuItemRect.Left < x && menuItemRect.Right > x)
    {
      if(ServiceLocator::GetAudio()->IsSongPlaying())
      {
        ServiceLocator::GetAudio()->StopAllSounds();
      }
      return (*it).action;
    }
  }
  return Nothing;
}
