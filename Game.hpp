#pragma once
#include <string>

class Game
{
public:
  Game();
  void Loop() const;
  void Exit() const;

private:
  void doSomethingLocal() const;

  int m_memberInt;
};