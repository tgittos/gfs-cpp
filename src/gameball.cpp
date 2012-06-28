#include "gameball.hpp"
#include <math.h>
#include "game.hpp"
#include "playerpaddle.hpp"
GameBall::GameBall() :
  _velocity(230.f),
  _elapsedTimeSinceStart(0.f)
{
  Load("assets/ball.png");
  assert(IsLoaded());

  GetSprite().SetCenter(15, 15);

  sf::Randomizer::SetSeed(std::clock());
  _angle = (float)sf::Randomizer::Random(0, 360);
}
GameBall::~GameBall()
{
}
void GameBall::Update(float elapsedTime)
{
  _elapsedTimeSinceStart += elapsedTime;

  if(_elapsedTimeSinceStart < 3.f)
  {
    return;
  }

  float distance = _velocity * elapsedTime;
  float moveX = LinearVelocityX(_angle) * distance;
  float moveY = LinearVelocityY(_angle) * distance;

  sf::Vector2f pos = GetPosition();
  float width = GetWidth();
  float height = GetHeight();

  if(pos.x - width / 2 <= 0 ||
     pos.x + width / 2 >= Game::SCREEN_WIDTH)
  {
    _angle = 360.f - _angle;
    // correct for edge to edge bounching
    if(_angle > 260.f && _angle < 280.f ||
       _angle > 80.f && _angle < 100.f)
    {
      _angle += 20.f;
    }
    moveX = -moveX;
  }

  PlayerPaddle* player1 = dynamic_cast<PlayerPaddle*>(Game::GetGameObjectManager().Get("Paddle1"));
  assert(NULL != player1);
  
  sf::Rect<float> player1BoundingBox = player1->GetBoundingRect();
  
  if(player1BoundingBox.Intersects(GetBoundingRect()))
  {
    _angle = fmodf((360.f - (_angle - 180.f)), 360.f);
    moveY = -moveY;
  
    // if situation where the ball is inside the paddle
    if(GetBoundingRect().Bottom > player1->GetBoundingRect().Top)
    {
      SetPosition(pos.x, player1->GetBoundingRect().Top - width / 2);
    }
  
    float playerVelocity = player1->GetVelocity();
    if (playerVelocity < 0)
    {
      _angle = fmodf(_angle - 20.f, 360.f);
    }
    if (playerVelocity > 0)
    {
      _angle = fmodf(_angle + 20.f, 360.f);
    }
  
    _velocity += 5.f;
  }

  if(pos.y - height / 2 <= 0)
  {
    _angle = 180 - _angle;
    moveY = -moveY;
  }

  if(pos.y + height / 2 >= Game::SCREEN_HEIGHT)
  {
    GetSprite().SetPosition(Game::SCREEN_WIDTH / 2, Game::SCREEN_HEIGHT / 2);
    _angle = (float)sf::Randomizer::Random(0, 360);
    _velocity = 220.f;
    _elapsedTimeSinceStart = 0.f;
  }

  GetSprite().Move(moveX, moveY);
}
float GameBall::LinearVelocityX(float angle)
{
  angle = fmodf(angle - 90.f, 360.f);
  return (float)cos(angle * ( 3.1415926 / 180.f ));
}
float GameBall::LinearVelocityY(float angle)
{
  angle = fmodf(angle -= 90.f, 360.f);
  return (float)sin(angle * (3.1415926 / 180.f ));
}
