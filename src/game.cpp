#include "game.hpp"
#include "splashscreen.hpp"
#include "mainmenu.hpp"
#include "playerpaddle.hpp"
#include "gameball.hpp"
void Game::Start(void)
{
  if(_gameState != Uninitialized)
    return;

  _mainWindow.Create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32),"Pang!");

  PlayerPaddle *player1 = new PlayerPaddle();
  player1->SetPosition((SCREEN_WIDTH / 2) - 45, 700);
  _gameObjectManager.Add("Paddle1", player1);

  GameBall *ball = new GameBall();
  ball->SetPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 15);
  _gameObjectManager.Add("Ball", ball);

  _gameState = Game::ShowingSplash;

  while(!IsExiting())
  {
    GameLoop();
  }

  _mainWindow.Close();
}
sf::RenderWindow& Game::GetWindow()
{
  return _mainWindow;
}
const sf::Input& Game::GetInput()
{
  return _mainWindow.GetInput();
}
bool Game::IsExiting()
{
  if(_gameState == Game::Exiting)
    return true;
  else
    return false;
}
void Game::ShowSplashScreen()
{
  SplashScreen splashScreen;
  splashScreen.Show(_mainWindow);
 _gameState = Game::ShowingMenu;
}
void Game::ShowMenu()
{
  MainMenu mainMenu;
  MainMenu::MenuResult result = mainMenu.Show(_mainWindow);
  switch(result)
  {
  case MainMenu::Exit:
     _gameState = Game::Exiting;
     break;
   case MainMenu::Play:
     _gameState = Game::Playing;
     break;
  }
}
void Game::GameLoop()
{
  sf::Event currentEvent;
  _mainWindow.GetEvent(currentEvent);

  switch(_gameState)
  {
    case Game::ShowingSplash:
      {
        ShowSplashScreen();
        break;
      }
    case Game::ShowingMenu:
      {
        ShowMenu();
        break;
      }
    case Game::Playing:
      {
        _mainWindow.Clear(sf::Color(0,0,0));
        _gameObjectManager.UpdateAll();
        _gameObjectManager.DrawAll(_mainWindow);
        _mainWindow.Display();

        if(currentEvent.Type == sf::Event::Closed)
        {
          _gameState = Game::Exiting;
        }
        if(currentEvent.Type == sf::Event::KeyPressed)
        {
          if(sf::Key::Escape == currentEvent.Key.Code)
          {
            ShowMenu();
          }
        }

        break;
      }
  }
}
Game::GameState Game::_gameState = Uninitialized;
sf::RenderWindow Game::_mainWindow;
GameObjectManager Game::_gameObjectManager;
