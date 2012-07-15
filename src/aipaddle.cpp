#include <math.h>
#include <iostream>
#include "aipaddle.hpp"
#include "game.hpp"
#include "gameball.hpp"

AIPaddle::AIPaddle()
{
  _paddleTargetX = Game::SCREEN_WIDTH / 2;
}

AIPaddle::~AIPaddle()
{
}

void AIPaddle::Update(float elapsedTime)
{
  const GameBall* gameBall = static_cast<GameBall*>(Game::GetGameObjectManager().Get("Ball"));
  sf::Vector2f ballPosition = gameBall->GetPosition();

  if (_lastBallPos.x == 0 && _lastBallPos.y == 0)
  {
    _lastBallPos = ballPosition;
  }
  if (_lastBallPos != ballPosition && (ballPosition.y - _lastBallPos.y) < 0)
  {
    float m = (ballPosition.y - _lastBallPos.y) / (ballPosition.x - _lastBallPos.x);
    float c = ballPosition.y - m * ballPosition.x;
  
    _paddleTargetX = (GetPosition().y - c) / m;
    if (_paddleTargetX < 0 || _paddleTargetX > Game::SCREEN_WIDTH)
    {
      if (_paddleTargetX < 0)
      {
        _paddleTargetX = -_paddleTargetX;
      }
      else
      {
        _paddleTargetX = Game::SCREEN_WIDTH - (_paddleTargetX - Game::SCREEN_WIDTH);
      }
      if (_paddleTargetX < 0 || _paddleTargetX > Game::SCREEN_WIDTH)
      {
        _paddleTargetX = GetPosition().x;
      }
    }
  }
  _lastBallPos = ballPosition;

  float acceleration = 4.f;
  if(GetPosition().x < _paddleTargetX)
  {
    if (_velocity < 0.f)
    {
      _velocity = 0.f;
    }
    _velocity += acceleration;
  }
  else if (GetPosition().x > _paddleTargetX)
  {
    if (_velocity > 0.f)
    {
      _velocity = 0.f;
    }
    _velocity -= acceleration;
  }
  else
  {
    _velocity = 0.f;
  }

  if (_velocity > _maxVelocity)
  {
    _velocity = _maxVelocity;
  }
  if (_velocity < -_maxVelocity)
  {
    _velocity = -_maxVelocity;
  }

  sf::Vector2f pos = GetPosition();
  sf::Vector2f spriteSize = GetSprite().GetSize();
  if(pos.x <= spriteSize.x / 2)
  {
    if(_velocity < 0)
    {
      _velocity = -_velocity;
    }
  }
  if(pos.x >= (Game::SCREEN_WIDTH - spriteSize.x / 2))
  {
    if(_velocity > 0)
    {
      _velocity = -_velocity;
    }
  }

  GetSprite().Move(_velocity * elapsedTime, 0);
}
