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
		auto Explosion1 = new AExplosion();
		Explosion1->SetLocation(Location.x, Location.y - 64);
		auto Explosion2 = new AExplosion();
		Explosion2->SetLocation(Location.x - 64, Location.y);
		auto Explosion3 = new AExplosion();
		Explosion3->SetLocation(Location);
		auto Explosion4 = new AExplosion();
		Explosion4->SetLocation(Location.x + 64, Location.y);
		auto Explosion5 = new AExplosion();
		Explosion5->SetLocation(Location.x, Location.y + 64);
	}
}
