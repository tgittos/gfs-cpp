#ifndef PLAYER_PADDLE_H
#define PLAYER_PADDLE_H

#include "game.hpp" // this is a crappy reference
#include "visiblegameobject.hpp"

class PlayerPaddle :
  public VisibleGameObject
{
public:
  PlayerPaddle();
  ~PlayerPaddle();

  void Update(float elapsedTime);

  float GetVelocity() const;

private:
  float _velocity;
  float _maxVelocity;
};

#endif
