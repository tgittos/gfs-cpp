#include "paddle.hpp"
Paddle::Paddle() :
  _velocity(0), _maxVelocity(600.0f)
{
  char path[] = "assets/paddle.png";
  Load(path);
  assert(IsLoaded());

  sf::Sprite& sprite = GetSprite();
  sf::Vector2f size = sprite.GetSize();
  sprite.SetCenter(size.x / 2, size.y / 2);
}
Paddle::~Paddle()
{
}
float Paddle::GetVelocity() const
{
  return _velocity;
}
