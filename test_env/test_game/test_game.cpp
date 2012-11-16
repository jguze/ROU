#include "Game.h"

int main(int argc, char *argv[])
{
  Game::Start((argc > 1 && *argv[1] == 's'));
  return 0;
}