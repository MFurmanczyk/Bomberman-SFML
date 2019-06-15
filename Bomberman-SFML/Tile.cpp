#include "Tile.h"

ATile::ATile() : APawn(new ATileController)
{
	//
}

void ATile::Draw()
{
	GGame::Instantiate().GetWindow().draw(Sprite);
}

