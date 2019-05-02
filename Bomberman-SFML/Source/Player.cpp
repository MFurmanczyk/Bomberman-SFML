#include "../Inlcudes/Core/Player.h"

void APlayer::Draw()
{
		GGame::Instantiate().GetWindow().draw(Sprite);
}

void APlayerController::Update(const float & DeltaTime)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		Pawn->SetLocation(Pawn->GetLocation().x - .5f, Pawn->GetLocation().y);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		Pawn->SetLocation(Pawn->GetLocation().x + .5f, Pawn->GetLocation().y);	
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		Pawn->SetLocation(Pawn->GetLocation().x, Pawn->GetLocation().y + .5f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		Pawn->SetLocation(Pawn->GetLocation().x, Pawn->GetLocation().y - .5f);
	}
}
