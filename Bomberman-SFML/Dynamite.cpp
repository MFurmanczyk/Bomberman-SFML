#include "Dynamite.h"

ADynamite::ADynamite() : APawn(new ADynamiteController)
{	
	Sprite.setTexture(*(TTextureManager::Get("Bomb")));
	GGame::Instantiate().GetLevel()->AddActor(this);
}

void ADynamite::Update(const float & DeltaTime)
{
	Controller->Update(DeltaTime);
}

void ADynamite::Draw()
{
	GGame::Instantiate().GetWindow().draw(this->Sprite);
}

void ADynamiteController::Update(const float & DeltaTime)
{
	ExplosionTime -= DeltaTime;
	if (ExplosionTime < 0.f)
	{
		sf::Vector2f Location = Pawn->GetLocation();
		GGame::Instantiate().GetLevel()->RemoveActor(Pawn);
		auto Explosion = new AExplosion();
		Explosion->SetLocation(Location);
	}
}
