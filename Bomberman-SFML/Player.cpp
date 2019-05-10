#include "Player.h"

void APlayerController::Update(const float & DeltaTime)
{
	Move();
}

void APlayerController::Move()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		Pawn->SetLocation(Pawn->GetLocation().x - .5f, Pawn->GetLocation().y);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		Pawn->SetLocation(Pawn->GetLocation().x + .5f, Pawn->GetLocation().y);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		Pawn->SetLocation(Pawn->GetLocation().x, Pawn->GetLocation().y + .5f);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		Pawn->SetLocation(Pawn->GetLocation().x, Pawn->GetLocation().y - .5f);
	}
}

APlayer::APlayer() : APawn(new APlayerController)
{
	Texture.loadFromFile("C:\\Users\\macie\\source\\repos\\Bomberman-SFML\\Bomberman-SFML\\Bomberman\\Front\\Bman_F_f00.png");
	Sprite.setTexture(Texture);
}

void APlayer::Draw()
{
	GGame::Instantiate().GetWindow().draw(Sprite);
}
