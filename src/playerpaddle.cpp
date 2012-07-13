#include "playerpaddle.hpp"
PlayerPaddle::PlayerPaddle()
{
}
PlayerPaddle::~PlayerPaddle()
{
}
void PlayerPaddle::Update(float elapsedTime)
{
  float acceleration = 4.f;
  if(Game::GetInput().IsKeyDown(sf::Key::Left))
  {
    if(_velocity > 0)
    {
      _velocity = 0.f;
    }
    _velocity -= acceleration;
  }
  if(Game::GetInput().IsKeyDown(sf::Key::Right))
  {
    if(_velocity < 0)
    {
      _velocity = 0.f;
    }
    _velocity += acceleration;
  }
  if(!Game::GetInput().IsKeyDown(sf::Key::Left) &&
     !Game::GetInput().IsKeyDown(sf::Key::Right))
  {
    float deceleration = 2.f;
    if (_velocity < -deceleration)
    {
      _velocity += deceleration;
    }
    else if (_velocity > deceleration)
    {
      _velocity -= deceleration;
    } else
    {
      _velocity = 0.f;
    }
  }

  if(_velocity > _maxVelocity)
  {
    _velocity = _maxVelocity;
  }
  if(_velocity < -_maxVelocity)
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
