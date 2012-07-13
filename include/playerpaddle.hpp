#ifndef PLAYER_PADDLE_H
#define PLAYER_PADDLE_H

#include "game.hpp" // this is a crappy reference
#include "paddle.hpp"

class PlayerPaddle :
  public Paddle
{
public:
  PlayerPaddle();
  ~PlayerPaddle();

  void Update(float elapsedTime);
};

#endif
