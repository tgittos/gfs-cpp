#include "game.hpp"
#include "splashscreen.hpp"
#include "mainmenu.hpp"
#include "playerpaddle.hpp"
#include "aipaddle.hpp"
#include "gameball.hpp"
#include "servicelocator.hpp"
#include "sfmlsoundprovider.hpp"
void Game::Start(void)
{
  if(_gameState != Uninitialized)
    return;

  _mainWindow.Create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32),"Pang!");

  SFMLSoundProvider soundProvider;
  ServiceLocator::RegisterAudioService(&soundProvider);
  ServiceLocator::GetAudio()->PlaySong("assets/Soundtrack.ogg",true);

  PlayerPaddle *player1 = new PlayerPaddle();
  player1->SetPosition(SCREEN_WIDTH / 2, _gameField.Bottom - 40);
  _gameObjectManager.Add("Paddle1", player1);

  AIPaddle* player2 = new AIPaddle();
  player2->SetPosition(SCREEN_WIDTH / 2, _gameField.Top + 40);
  _gameObjectManager.Add("Paddle2", player2);

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
GameObjectManager& Game::GetGameObjectManager()
{
  return _gameObjectManager;
}
const sf::Rect<int> Game::GetGameField()
{
  return _gameField;
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
        _gui.Draw(_mainWindow);
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
GUI Game::_gui;
sf::Rect<int> Game::_gameField(0, 50, SCREEN_WIDTH, SCREEN_HEIGHT - 25);
