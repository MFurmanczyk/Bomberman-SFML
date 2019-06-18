#include "Explosion.h"

AExplosion::AExplosion() : APawn (new AExplosionController)
{
	Sprite.setTexture(*(TTextureManager::Get("Explosion")));
	GGame::Instantiate().GetLevel()->AddActor(this);
	
}

void AExplosion::Update(const float & DeltaTime)
{
	Collider = sf::FloatRect(this->GetLocation(), sf::Vector2f(this->Sprite.getTexture()->getSize()));
	Controller->Update(DeltaTime);
	DestroyTile();
}

void AExplosion::Draw()
{
	GGame::Instantiate().GetWindow().draw(this->Sprite);
}

bool AExplosion::DestroyTile()
{
	auto Tiles = GGame::Instantiate().GetLevel()->GetExplodableTiles();
	
	for (auto Tile : Tiles)
	{
		auto TempTile = dynamic_cast<AExplodableTile*> (Tile);
		if (Tile)
		{
			if (this->Collider.intersects(TempTile->GetCollider()))
			{
				GGame::Instantiate().GetLevel()->RemoveActor(Tile);
				return true;
			}
		}
	}
	return false;
}

void AExplosionController::Update(const float & DeltaTime)
{
	Duration -= DeltaTime;
	if (Duration <= 0.f)
	{
		GGame::Instantiate().GetLevel()->RemoveActor(this->Pawn);
	}
}
