#include <sstream>
#include "gui.hpp"
#include "game.hpp"
#include "gameball.hpp"

GUI::GUI()
{
}

GUI::~GUI()
{
}

void GUI::Draw(sf::RenderWindow& window)
{
  GameBall* ball = dynamic_cast<GameBall*>(Game::GetGameObjectManager().Get("Ball"));

  std::ostringstream player1out;
  player1out << "Player 1: " << ball->GetPlayer1Score();
  sf::String player1(player1out.str());

  std::ostringstream aiout;
  aiout << "Player 2: " << ball->GetAIScore();
  sf::String ai(aiout.str());

  ai.SetX(600);
  window.Draw(player1);
  window.Draw(ai);
}
