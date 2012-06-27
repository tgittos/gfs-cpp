#include "gameball.hpp"
GameBall::GameBall()
{
  Load("assets/ball.png");
  assert(IsLoaded());

  GetSprite().SetCenter(15, 15);
}
GameBall::~GameBall()
{
}
void GameBall::Update(float elapsedTime)
{
}
