#include "aipaddle.hpp"
#include "game.hpp"
#include "gameball.hpp"

AIPaddle::AIPaddle():
  _velocity(0),
  _maxVelocity(600.f)
{
  Load("assets/paddle.png");
  assert(IsLoaded());

  GetSprite().SetCenter(GetSprite().GetSize().x / 2, GetSprite().GetSize().y / 2);
}

AIPaddle::~AIPaddle()
{
}

void AIPaddle::Update(float elapsedTime)
{
  const GameBall* gameBall = static_cast<GameBall*>(Game::GetGameObjectManager().Get("Ball"));
  sf::Vector2f ballPosition = gameBall->GetPosition();

  if(GetPosition().x - 20 < ballPosition.x)
  {
    _velocity += 15.f;
  }
  else if (GetPosition().x + 20 > ballPosition.x)
  {
    _velocity -= 15.f;
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

float AIPaddle::GetVelocity() const
{
  return _velocity;
}
