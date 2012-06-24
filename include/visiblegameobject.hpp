#ifndef VISIBLE_GAME_OBJECT_H
#define VISIBLE_GAME_OBJECT_H

#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"

class VisibleGameObject
{
public:
  VisibleGameObject();
  virtual ~VisibleGameObject();

  virtual void Load(std::string filename);
  virtual void Draw(sf::RenderWindow& window);
  virtual void SetPosition(float x, float y);

private:
  sf::Sprite _sprite;
  sf::Image _image;
  std::string _filename;
  bool _isLoaded;
};

#endif
