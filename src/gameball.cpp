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
  // serve to player first
  _angle = (float)sf::Randomizer::Random(45, 135) + 90.f;
}
GameBall::~GameBall()
{
}
void GameBall::Update(float elapsedTime)
{
  if (elapsedTime < 1.f)
  {
    // if we take more than 1 second to render a frame,
    // we've probably just come from the menu
    // and we should ignore it
    _elapsedTimeSinceStart += elapsedTime;
  }

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

  bool atTop = true;
  bool atBottom = false;
  if (pos.y > Game::SCREEN_HEIGHT / 2)
  {
    atTop = !atTop;
    atBottom = !atBottom;
  }

  if(pos.x - width / 2 <= 0 ||
     pos.x + width / 2 >= Game::SCREEN_WIDTH)
  {
    _angle = 360.f - _angle;
    moveX = -moveX;
  
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
      if(_angle > 90 && _angle < 270)
      {
        _angle -= 20.f;
      }
      else
      {
        _angle += 20.f;
      }
    }
  
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
      _angle = fmodf((360.f - (_angle - 180.f)), 360.f);
  
      float playerVelocity = player->GetVelocity();
      bool playerMovingLeft = false;
      bool playerMovingRight = false;
      float angleAdjust = 20.f;
      if (playerVelocity < 0)
      {
        playerMovingLeft = true;
      }
      if (playerVelocity > 0)
      {
        playerMovingRight = true;
      }
      
      // if the ball was moving left
      if (_angle > 180)
      {
        _velocity += 5.f;
        if (playerMovingLeft && _angle - angleAdjust > 290)
        {
          _angle -= angleAdjust;
        }
        if (playerMovingRight && _angle + angleAdjust < 320)
        {
          _angle += angleAdjust;
        }
      }
      // if the ball is moving right
      if (_angle < 180)
      {
        _velocity += 5.f;
        if (playerMovingLeft && _angle - angleAdjust > 40)
        {
          _angle -= angleAdjust;
        }
        if (playerMovingRight && _angle + angleAdjust < 120)
        {
          _angle += angleAdjust;
        }
      }
      _angle = fmodf(_angle, 360.f);
  
      bool struckLeft = false;
      bool struckRight = false;
      
      // value we want to compare - value to compare to < tolerance
      int tolerance = 5;
      if(pos.x + (width / 2) - playerBoundingBox.Left < tolerance)
      {
        struckLeft = true;
        if (atTop)
        {
          _angle = 315.f;
        }
        else
        {
          _angle = 225.f;
        }
        _velocity += 20.f;
      
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
        _velocity += 20.f;
      }
  
      // correct for edge to edge bounching
      if(_angle > 260.f && _angle < 280.f ||
         _angle > 80.f && _angle < 100.f)
      {
        if(_angle > 90 && _angle < 270)
        {
          _angle -= 20.f;
        }
        else
        {
          _angle += 20.f;
        }
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

  sf::Rect<int> gameField = Game::GetGameField();
  if(pos.y + height / 2 >= gameField.Bottom ||
     pos.y - height / 2 <= gameField.Top)
  {
    if(atTop)
    {
      // Increment player 1 score
      Game::Player1Scored();
    }
    else
    {
      // Increment AI score
      Game::AIScored();
    }
  
    GetSprite().SetPosition(Game::SCREEN_WIDTH / 2, Game::SCREEN_HEIGHT / 2);
    if (atTop)
    {
      // player 1 won, so serve to player 2
      _angle = fmodf((float)sf::Randomizer::Random(45, 135) - 90.f, 360.f);
    }
    else
    {
      // serve to player 1
      _angle = fmodf((float)sf::Randomizer::Random(45, 135) + 90.f, 360.f);
    }
    _velocity = 220.f;
    _elapsedTimeSinceStart = 0.f;
  
    ServiceLocator::GetAudio()->PlaySound("assets/miss.wav");
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
