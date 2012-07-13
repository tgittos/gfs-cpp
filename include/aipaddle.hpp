#ifndef AI_PADDLE_H
#define AI_PADDLE_H

#include "paddle.hpp"

class AIPaddle :
  public Paddle
{
public:
  AIPaddle(void);
  ~AIPaddle(void);

  void Update(float elapsedTime);
};

#endif
