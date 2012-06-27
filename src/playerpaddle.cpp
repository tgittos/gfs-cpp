#include "playerpaddle.hpp"
PlayerPaddle::PlayerPaddle() :
  _velocity(0), _maxVelocity(600.0f)
{
  char path[] = "assets/paddle.png";
  Load(path);
  assert(IsLoaded());

  sf::Sprite& sprite = GetSprite();
  sf::Vector2f size = sprite.GetSize();
  sprite.SetCenter(size.x / 2, size.y / 2);
}
PlayerPaddle::~PlayerPaddle()
{
}
float PlayerPaddle::GetVelocity() const
{
  return _velocity;
}
void PlayerPaddle::Update(float elapsedTime)
{
  if(Game::GetInput().IsKeyDown(sf::Key::Left))
  {
    _velocity -= 3.f;
  }
  if(Game::GetInput().IsKeyDown(sf::Key::Right))
  {
    _velocity += 3.f;
  }
  if(!Game::GetInput().IsKeyDown(sf::Key::Left) &&
     !Game::GetInput().IsKeyDown(sf::Key::Right))
  {
    float deceleration = 2.;
    if (_velocity < -deceleration)
    {
      _velocity += deceleration;
    } else if (_velocity > deceleration)
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
