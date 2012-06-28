#ifndef VISIBLE_GAME_OBJECT_H
#define VISIBLE_GAME_OBJECT_H

#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include <cassert>

class VisibleGameObject
{
public:
  VisibleGameObject();
  virtual ~VisibleGameObject();

  virtual void Load(std::string filename);
  virtual void Draw(sf::RenderWindow& window);
  virtual void Update(float elapsedTime) =0;

  virtual void SetPosition(float x, float y);
  virtual sf::Vector2f GetPosition() const;
  virtual float GetWidth() const;
  virtual float GetHeight() const;
  virtual sf::Rect<float> GetBoundingRect() const;
  virtual bool IsLoaded() const;

protected:
  sf::Sprite& GetSprite();

private:
  sf::Sprite _sprite;
  sf::Image _image;
  std::string _filename;
  bool _isLoaded;
};

#endif
