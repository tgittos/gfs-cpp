#include <math.h>
#include <iostream>
#include <string>
#include "gameball.hpp"
#include "game.hpp"
#include "playerpaddle.hpp"
#include "aipaddle.hpp"
#include "servicelocator.hpp"
GameBall::GameBall() :
  _velocity(230.f),
  _elapsedTimeSinceStart(0.f)
{
  Load("assets/ball.png");
  assert(IsLoaded());

  GetSprite().SetCenter(15, 15);

  sf::Randomizer::SetSeed(std::clock());
  _angle = (float)sf::Randomizer::Random(0, 360);
}
GameBall::~GameBall()
{
}
void GameBall::Update(float elapsedTime)
{
  _elapsedTimeSinceStart += elapsedTime;

  if(_elapsedTimeSinceStart < 3.f)
  {
    return;
  }

  float distance = _velocity * elapsedTime;
  float moveX = LinearVelocityX(_angle) * distance;
  float moveY = LinearVelocityY(_angle) * distance;

  sf::Vector2f pos = GetPosition();
  float width = GetWidth();
  float height = GetHeight();

  if(pos.x - width / 2 <= 0 ||
     pos.x + width / 2 >= Game::SCREEN_WIDTH)
  {
    _angle = 360.f - _angle;
  
    // set the ball at the edge of the screen
    if(pos.x - width / 2 <= 0)
    {
      SetPosition(width / 2, pos.y);
    }
    else if(pos.x + width / 2 >= Game::SCREEN_WIDTH)
    {
      SetPosition(Game::SCREEN_WIDTH - width / 2, pos.y);
    }
  
    // correct for edge to edge bounching
    if(_angle > 260.f && _angle < 280.f ||
       _angle > 80.f && _angle < 100.f)
    {
      _angle += 20.f;
    }
    moveX = -moveX;
  
    ServiceLocator::GetAudio()->PlaySound("assets/wall-hit.wav");
  }

  sf::Rect<float> ballBoundingBox = GetBoundingRect();
  std::vector<std::string> players;
  players.push_back("Paddle1");
  players.push_back("Paddle2");
  for(unsigned int i = 0; i < players.size(); i++)
  {
    Paddle* player = dynamic_cast<Paddle*>(Game::GetGameObjectManager().Get(players[i]));
    assert(NULL != player);
  
    sf::Rect<float> playerBoundingBox = player->GetBoundingRect();
  
    if(playerBoundingBox.Intersects(ballBoundingBox))
    {
      moveY = -moveY;
  
      bool atTop = true;
      bool atBottom = false;
      if (pos.y > Game::SCREEN_HEIGHT / 2)
      {
        atTop = !atTop;
        atBottom = !atBottom;
      }
  
      float playerVelocity = player->GetVelocity();
      if (playerVelocity < 0)
      {
        _angle = fmodf(_angle - 20.f, 360.f);
      }
      if (playerVelocity > 0)
      {
        _angle = fmodf(_angle + 20.f, 360.f);
      }
  
      bool struckLeft = false;
      bool struckRight = false;
      
      if(pos.x <= playerBoundingBox.Left ||
         pos.x >= playerBoundingBox.Right)
      {
        std::cout << "player hit the ball a glancing blow" << std::endl;
      
        _angle = -fmodf(_angle - 180.f, 360.f);
      
        // value we want to compare - value to compare to < tolerance
        int tolerance = 5;
        if(pos.x + (width / 2) - playerBoundingBox.Left < tolerance)
        {
          std::cout << "player struck ball with the side of the paddle" << std::endl;
          struckLeft = true;
          if (atTop)
          {
            _angle = 315.f;
          }
          else
          {
            _angle = 225.f;
          }
      
        }
        if (pos.x - (width / 2) - playerBoundingBox.Right > -tolerance)
        {
          struckRight = true;
          if (atTop)
          {
            _angle = 45.f;
          }
          else
          {
            _angle = 135.f;
          }
        }
      }
      else
      {
        _angle = fmodf((360.f - (_angle - 180.f)), 360.f);
      }
  
      if (atBottom && !struckLeft && !struckRight && ballBoundingBox.Bottom > playerBoundingBox.Top)
      {
        SetPosition(pos.x, playerBoundingBox.Top - width / 2);
      }
      if (atTop && !struckLeft && !struckRight && ballBoundingBox.Top < playerBoundingBox.Bottom)
      {
        SetPosition(pos.x, playerBoundingBox.Bottom + width / 2);
      }
      if(struckLeft && ballBoundingBox.Left > playerBoundingBox.Right)
      {
        SetPosition(playerBoundingBox.Left - width / 2, pos.y);
      }
      if (struckRight && ballBoundingBox.Left < playerBoundingBox.Right)
      {
        SetPosition(playerBoundingBox.Right + width / 2, pos.y);
      }
  
      _velocity += 5.f;
  
      ServiceLocator::GetAudio()->PlaySound("assets/paddle-hit.wav");
    }
  }

  if(pos.y + height / 2 >= Game::SCREEN_HEIGHT ||
     pos.y - height / 2 <= 0)
  {
    GetSprite().SetPosition(Game::SCREEN_WIDTH / 2, Game::SCREEN_HEIGHT / 2);
    _angle = (float)sf::Randomizer::Random(0, 360);
    _velocity = 220.f;
    _elapsedTimeSinceStart = 0.f;
  }

  GetSprite().Move(moveX, moveY);
}
float GameBall::LinearVelocityX(float angle)
{
  angle = fmodf(angle - 90.f, 360.f);
  return (float)cos(angle * ( 3.1415926 / 180.f ));
}
float GameBall::LinearVelocityY(float angle)
{
  angle = fmodf(angle -= 90.f, 360.f);
  return (float)sin(angle * (3.1415926 / 180.f ));
}
