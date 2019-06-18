#include "Tile.h"
#include "Speedup.h"


ATile::ATile() : APawn(new ATileController)
{
	
}

void ATile::Draw()
{
	GGame::Instantiate().GetWindow().draw(Sprite);
}

AExplodableTile::~AExplodableTile()

{
	if ((int)rand() % 5 == 0 && GGame::Instantiate().GetState() != EState::Ended)
	{
		auto SpeedUp = new ASpeedUp();
		SpeedUp->SetLocation(this->GetLocation().x + 16, this->GetLocation().y + 16);
	}
}

void AExplodableTile::SetCollider(sf::Vector2f _Position)
{
	this->Collider = sf::FloatRect(_Position, sf::Vector2f(this->Sprite.getTexture()->getSize()));
}

void ASolidTile::SetCollider(sf::Vector2f _Position)
{
	this->Collider = sf::FloatRect(_Position, sf::Vector2f(this->Sprite.getTexture()->getSize()));
}
