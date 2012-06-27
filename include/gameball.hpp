#ifndef GAME_BALL_H
#define GAME_BALL_H

#include "visiblegameobject.hpp"

class GameBall :
  public VisibleGameObject
{
public:
  GameBall();
  virtual ~GameBall();

  void Update(float elaspedTime);
};

#endif
