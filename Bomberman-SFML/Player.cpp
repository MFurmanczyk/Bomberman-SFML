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
		Pawn->SetLocation(Pawn->GetLocation().x - Velocity, Pawn->GetLocation().y);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		Pawn->SetLocation(Pawn->GetLocation().x + Velocity, Pawn->GetLocation().y);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		Pawn->SetLocation(Pawn->GetLocation().x, Pawn->GetLocation().y + Velocity);
		
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		Pawn->SetLocation(Pawn->GetLocation().x, Pawn->GetLocation().y - Velocity);
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
	Sprite.setTexture(*(TTextureManager::Get("BombermanFront")));
	Sprite.setOrigin(32, 91);
}

void APlayer::Draw()
{
	GGame::Instantiate().GetWindow().draw(Sprite);
}

void APlayer::Update(const float & DeltaTime)
{
	APawn::Update(DeltaTime);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		Sprite.setTexture(*(TTextureManager::Get("BombermanSide")));
		Sprite.setScale(-1, 1);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		Sprite.setTexture(*(TTextureManager::Get("BombermanSide")));
		Sprite.setScale(1, 1);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		Sprite.setTexture(*(TTextureManager::Get("BombermanFront")));
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		Sprite.setTexture(*(TTextureManager::Get("BombermanBack")));
	}
}
