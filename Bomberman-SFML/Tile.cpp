#include "Tile.h"

ATile::ATile() : APawn(new ATileController)
{
	
}

void ATile::Draw()
{
	GGame::Instantiate().GetWindow().draw(Sprite);
}

void AExplodableTile::SetCollider(sf::Vector2f _Position)
{
	this->Collider = sf::FloatRect(_Position, sf::Vector2f(this->Sprite.getTexture()->getSize()));
}

void ASolidTile::SetCollider(sf::Vector2f _Position)
{
	this->Collider = sf::FloatRect(_Position, sf::Vector2f(this->Sprite.getTexture()->getSize()));
}
