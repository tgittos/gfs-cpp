#include "visiblegameobject.hpp"
VisibleGameObject::VisibleGameObject()
{
  _isLoaded = false;
}
VisibleGameObject::~VisibleGameObject()
{
}
void VisibleGameObject::Load(std::string filename)
{
  if(!_image.LoadFromFile(filename))
  {
    _filename = "";
    _isLoaded = false;
  } else {
    _filename = filename;
    _sprite.SetImage(_image);
    _isLoaded = true;
  }
}
void VisibleGameObject::Draw(sf::RenderWindow& window)
{
  if(_isLoaded)
  {
    window.Draw(_sprite);
  }
}
void VisibleGameObject::SetPosition(float x, float y)
{
  if(_isLoaded)
  {
    _sprite.SetPosition(x, y);
  }
}
sf::Vector2f VisibleGameObject::GetPosition() const
{
  if(_isLoaded)
  {
    return _sprite.GetPosition();
  }
  return sf::Vector2f();
}
sf::Sprite& VisibleGameObject::GetSprite()
{
  return _sprite;
}
bool VisibleGameObject::IsLoaded() const
{
  return _isLoaded;
}
