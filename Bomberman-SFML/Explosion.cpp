#include "Explosion.h"

AExplosion::AExplosion() : APawn (new AExplosionController)
{
	Sprite.setTexture(*(TTextureManager::Get("Explosion")));
	GGame::Instantiate().GetLevel()->AddActor(this);
}

void AExplosion::Update(const float & DeltaTime)
{
	Controller->Update(DeltaTime);
}

void AExplosion::Draw()
{
	GGame::Instantiate().GetWindow().draw(this->Sprite);
}

void AExplosionController::Update(const float & DeltaTime)
{
	Duration -= DeltaTime;
	if (Duration <= 0.f)
	{
		GGame::Instantiate().GetLevel()->RemoveActor(Pawn);
	}
}
