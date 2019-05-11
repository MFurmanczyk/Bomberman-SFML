#include "Player.h"

void APlayerController::Update(const float & DeltaTime)
{
	auto& Game = GGame::Instantiate();
	Move();
	Plant();
	if (!Game.GetLevel()->ActorExists(Dynamite))
	{
		Dynamite = nullptr;
		Setter = false;
	}
}

void APlayerController::Move()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		Pawn->SetLocation(Pawn->GetLocation().x - 2.5f, Pawn->GetLocation().y);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		Pawn->SetLocation(Pawn->GetLocation().x + 2.5f, Pawn->GetLocation().y);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		Pawn->SetLocation(Pawn->GetLocation().x, Pawn->GetLocation().y + 2.5f);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		Pawn->SetLocation(Pawn->GetLocation().x, Pawn->GetLocation().y - 2.5f);
	}
}

void APlayerController::Plant()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		if (!Dynamite)
		{
			Dynamite = new ADynamite();
		}
	}
	if (Dynamite and !Setter)
	{
		Dynamite->SetLocation(this->Pawn->GetLocation());
		Setter = true;
	}
}

APlayer::APlayer() : APawn(new APlayerController)
{
	GGame::Instantiate().GetLevel()->AddActor(this);
	Texture.loadFromFile("C:\\Users\\macie\\source\\repos\\Bomberman-SFML\\Bomberman-SFML\\Bomberman\\Front\\Bman_F_f00.png");
	Sprite.setTexture(Texture);
}

void APlayer::Draw()
{
	GGame::Instantiate().GetWindow().draw(Sprite);
}
