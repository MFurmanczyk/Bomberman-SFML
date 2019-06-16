#include "Player.h"
#include <typeinfo>

void APlayerController::Update(const float & DeltaTime)
{
	auto& Game = GGame::Instantiate();
	Move(DeltaTime);
	Plant();
	if (!Game.GetLevel()->ActorExists(Dynamite))
	{
		Dynamite = nullptr;
		Setter = false;
	}
	std::cout << this->Pawn->GetLocation().x << " " << this->Pawn->GetLocation().y << std::endl;
}

void APlayerController::Move(const float& DeltaTime)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		this->MoveLeft(DeltaTime);
		std::cout << this->Pawn->GetLocation().x << " " << this->Pawn->GetLocation().y << std::endl;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		this->MoveRight(DeltaTime);
		std::cout << this->Pawn->GetLocation().x << " " << this->Pawn->GetLocation().y << std::endl;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		this->MoveDown(DeltaTime);
		std::cout << this->Pawn->GetLocation().x << " " << this->Pawn->GetLocation().y << std::endl;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		this->MoveUp(DeltaTime);
		std::cout << this->Pawn->GetLocation().x << " " << this->Pawn->GetLocation().y << std::endl;
	}
}

void APlayerController::MoveLeft(const float& DeltaTime)
{
	sf::Vector2f PawnLocation = Pawn->GetLocation();
	Pawn->SetLocation(Pawn->GetLocation().x - Velocity * DeltaTime, Pawn->GetLocation().y);
	dynamic_cast<APlayer*> (Pawn)->SetDirection(EDirection::ELeft);
	if (dynamic_cast<APlayer*> (Pawn)->IsColliding())
	{
		Pawn->SetLocation(PawnLocation);
	}
}

void APlayerController::MoveRight(const float& DeltaTime)
{
	sf::Vector2f PawnLocation = Pawn->GetLocation();
	Pawn->SetLocation(Pawn->GetLocation().x + Velocity * DeltaTime, Pawn->GetLocation().y);
	dynamic_cast<APlayer*> (Pawn)->SetDirection(EDirection::ERight);
	if (dynamic_cast<APlayer*> (Pawn)->IsColliding())
	{
		Pawn->SetLocation(PawnLocation);
	}
}

void APlayerController::MoveDown(const float& DeltaTime)
{
	sf::Vector2f PawnLocation = Pawn->GetLocation();
	Pawn->SetLocation(Pawn->GetLocation().x, Pawn->GetLocation().y + Velocity * DeltaTime);
	dynamic_cast<APlayer*> (Pawn)->SetDirection(EDirection::EDown);
	if (dynamic_cast<APlayer*> (Pawn)->IsColliding())
	{
		Pawn->SetLocation(PawnLocation);
	}
}

void APlayerController::MoveUp(const float& DeltaTime)
{
	sf::Vector2f PawnLocation = Pawn->GetLocation();
	Pawn->SetLocation(Pawn->GetLocation().x, Pawn->GetLocation().y - Velocity * DeltaTime);
	dynamic_cast<APlayer*> (Pawn)->SetDirection(EDirection::EUp);
	if (dynamic_cast<APlayer*> (Pawn)->IsColliding())
	{
		Pawn->SetLocation(PawnLocation);
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
	Sprite.setOrigin(32, 96);
	Collider = sf::FloatRect(sf::Vector2f(this->GetLocation().x - 32, this->GetLocation().y - 32), sf::Vector2f(40, 40));
}

void APlayer::Draw()
{
	GGame::Instantiate().GetWindow().draw(Sprite);
}

void APlayer::Update(const float & DeltaTime)
{
	Collider = sf::FloatRect(sf::Vector2f(this->GetLocation().x - 32.f, this->GetLocation().y - 32.f), sf::Vector2f(40, 40));
	APawn::Update(DeltaTime);
	if (GetDirection() == EDirection::ELeft )
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
	else if (GetDirection() == EDirection::EUp )
	{
		Sprite.setTexture(*(TTextureManager::Get("BombermanBack")));
	}
}

bool APlayer::IsColliding()
{
	auto Tiles = GGame::Instantiate().GetLevel()->GetCollidableTiles();
	for (auto Tile : Tiles)
	{
		auto TempTile = dynamic_cast<ATile*> (Tile);
		if (Tile)
		{
			if (this->GetCollider().intersects(TempTile->GetCollider()))
			{
				return true;
			}
		}
	}
	return false;
}
