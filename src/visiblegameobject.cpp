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

    //debug
    /*
    sf::Rect<float> boundingBox = GetBoundingRect();
    sf::Shape debugBox = sf::Shape::Rectangle(
      boundingBox.Left, boundingBox.Top,
      boundingBox.Right, boundingBox.Bottom,
      sf::Color::Blue,
      true,
      sf::Color::Blue
    );
    debugBox.SetOutlineWidth(2);
    debugBox.EnableFill(false);
    window.Draw(debugBox);
    */
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

float VisibleGameObject::GetWidth() const
{
  if(_isLoaded)
  {
    return _sprite.GetSize().x;
  }
  return 0.f;
}

float VisibleGameObject::GetHeight() const
{
  if(_isLoaded)
  {
    return _sprite.GetSize().y;
  }
  return 0.f;
}

sf::Rect<float> VisibleGameObject::GetBoundingRect() const
{
  sf::Vector2f size = _sprite.GetSize();
  sf::Vector2f pos = _sprite.GetPosition();

  return sf::Rect<float>(
    pos.x - size.x / 2,
    pos.y - size.y / 2,
    pos.x + size.x / 2,
    pos.y + size.y / 2
  );
}

sf::Sprite& VisibleGameObject::GetSprite()
{
  return _sprite;
}

bool VisibleGameObject::IsLoaded() const
{
  return _isLoaded;
}
