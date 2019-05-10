#include "Game.h"

int main()
{
	auto& Game = GGame::Instantiate();
	Game.Run();
	return 0;
}