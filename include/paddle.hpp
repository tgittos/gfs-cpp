#ifndef PADDLE_H
#define PADDLE_H

#include "game.hpp" // this is a crappy reference
#include "visiblegameobject.hpp"

class Paddle :
  public VisibleGameObject
{
public:
  Paddle();
  ~Paddle();

  float GetVelocity() const;

protected:
  float _velocity;
  float _maxVelocity;
};

#endif
