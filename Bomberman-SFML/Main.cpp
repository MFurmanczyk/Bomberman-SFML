#include "Game.h"
#include <ctime>

int main()
{
	srand(time(NULL));
	GGame::Instantiate().Run();
	return 0;
}