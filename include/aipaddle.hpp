#ifndef AI_PADDLE_H
#define AI_PADDLE_H

#include "visiblegameobject.hpp"

class AIPaddle :
  public VisibleGameObject
{
public:
  AIPaddle(void);
  ~AIPaddle(void);

  void Update(float elapsedTime);

  float GetVelocity() const;

private:
  float _velocity;
  float _maxVelocity;
};

#endif
