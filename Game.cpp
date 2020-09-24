#include "Game.hpp"
#include <iostream>

Game::Game() : m_memberInt(1)
{
}

void Game::Loop() const
{
  std::cout << m_memberInt << std::endl;
}

void Game::Exit() const {}
void Game::doSomethingLocal() const {}
