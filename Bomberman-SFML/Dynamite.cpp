#include "Dynamite.h"

ADynamite::ADynamite()
{
	Texture.loadFromFile("C:\\Users\\macie\\source\\repos\\Bomberman-SFML\\Bomberman-SFML\\Bomberman\\Bomb\\Bomb_f01.png");
	Sprite.setTexture(Texture);
	GGame::Instantiate().GetLevel()->AddActor(this);
}

void ADynamite::Update(const float & DeltaTime)
{
	this->Explode(DeltaTime);
}

void ADynamite::Draw()
{
	GGame::Instantiate().GetWindow().draw(Sprite);
}

void ADynamite::Explode(const float & DeltaTime)
{
	ExplodeTime += DeltaTime;
	if (ExplodeTime > 2.f)
	{
		GGame::Instantiate().GetLevel()->RemoveActor(this);
	}
}
