#include "game.hpp"
void Game::Start(void)
{
  if(_gameState != Uninitialized)
    return;

  _mainWindow.Create(sf::VideoMode(1024,768,32),"Pang!");
  _gameState = Game::Playing;

  while(!IsExiting())
  {
    GameLoop();
  }

  _mainWindow.Close();
}
bool Game::IsExiting()
{
  if(_gameState == Game::Exiting)
    return true;
  else
    return false;
}
void Game::GameLoop()
{
  sf::Event currentEvent;
  while(_mainWindow.GetEvent(currentEvent))
  {

    switch(_gameState)
    {
      case Game::Playing:
        {
          _mainWindow.Clear(sf::Color(255,0,0));
          _mainWindow.Display();

          if(currentEvent.Type == sf::Event::Closed)
            {
              _gameState = Game::Exiting;
            }
          break;
        }
    }
  }
}


Game::GameState Game::_gameState = Uninitialized;
sf::RenderWindow Game::_mainWindow;
