#include "Speedup.h"

ASpeedUp::ASpeedUp()
{
	this->Sprite.setTexture(*(TTextureManager::Get("Speedup")));
	GGame::Instantiate().GetLevel()->AddActor(this);
}

ASpeedUp::~ASpeedUp()
{

}

void ASpeedUp::Update(const float & DeltaTime)
{
	Collider = sf::FloatRect(this->GetLocation(), sf::Vector2f(this->Sprite.getTexture()->getSize()));
}

void ASpeedUp::Draw()
{
	GGame::Instantiate().GetWindow().draw(this->Sprite);
}