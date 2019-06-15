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

	auto Owner = dynamic_cast<APlayer*> (Pawn);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		Pawn->SetLocation(Pawn->GetLocation().x - Velocity, Pawn->GetLocation().y);
		Owner->SetDirection(EDirection::ELeft);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		Pawn->SetLocation(Pawn->GetLocation().x + Velocity, Pawn->GetLocation().y);
		Owner->SetDirection(EDirection::ERight);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		Pawn->SetLocation(Pawn->GetLocation().x, Pawn->GetLocation().y + Velocity);
		Owner->SetDirection(EDirection::EDown);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		Pawn->SetLocation(Pawn->GetLocation().x, Pawn->GetLocation().y - Velocity);
		Owner->SetDirection(EDirection::EUp);
	}
}

void APlayerController::Plant()
{
	unsigned BombDisplacement = 8u; //Variable to centre the bomb on a tile
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		if (!Dynamite)
		{
			Dynamite = new ADynamite();
			
		}
	}
	if (Dynamite and !Setter)
	{
		Dynamite->SetLocation((int(this->Pawn->GetLocation().x / 64) * 64) + BombDisplacement,
							  (int(this->Pawn->GetLocation().y / 64) * 64) + BombDisplacement); // 64x64 - size of a tile
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
	if (GetDirection() == EDirection::ELeft)
	{
		Sprite.setTexture(*(TTextureManager::Get("BombermanSide")));
		Sprite.setScale(-1, 1);
	}
	else if (GetDirection() == EDirection::ERight)
	{
		Sprite.setTexture(*(TTextureManager::Get("BombermanSide")));
		Sprite.setScale(1, 1);
	}
	else if (GetDirection() == EDirection::EDown)
	{
		Sprite.setTexture(*(TTextureManager::Get("BombermanFront")));
	}
	else if (GetDirection() == EDirection::EUp)
	{
		Sprite.setTexture(*(TTextureManager::Get("BombermanBack")));
	}
}
