#include "FirstPlayer.h"
#include <typeinfo>
#include "Speedup.h"

void AFirstPlayerController::Update(const float & DeltaTime)
{
	auto& Game = GGame::Instantiate();
	Move(DeltaTime);
	Plant();
	if (!Game.GetLevel()->ActorExists(Dynamite))
	{
		Dynamite = nullptr;
		Setter = false;
	}
	dynamic_cast<AFirstPlayer*>(Pawn)->IsOverlappingSpeedUp();
}

void AFirstPlayerController::Move(const float& DeltaTime)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		this->MoveLeft(DeltaTime);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		this->MoveRight(DeltaTime);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		this->MoveDown(DeltaTime);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		this->MoveUp(DeltaTime);
	}
}

void AFirstPlayerController::MoveLeft(const float& DeltaTime)
{
	sf::Vector2f PawnLocation = Pawn->GetLocation();
	Pawn->SetLocation(Pawn->GetLocation().x - dynamic_cast<AFirstPlayer*> (Pawn)->GetVelocity() * DeltaTime, Pawn->GetLocation().y);
	dynamic_cast<AFirstPlayer*> (Pawn)->SetCollider();
	dynamic_cast<AFirstPlayer*> (Pawn)->SetDirection(EDirection::ELeft);
	if (dynamic_cast<AFirstPlayer*> (Pawn)->IsColliding())
	{
		Pawn->SetLocation(PawnLocation);
		dynamic_cast<AFirstPlayer*> (Pawn)->SetCollider();
	}
}

void AFirstPlayerController::MoveRight(const float& DeltaTime)
{
	sf::Vector2f PawnLocation = Pawn->GetLocation();
	Pawn->SetLocation(Pawn->GetLocation().x + dynamic_cast<AFirstPlayer*> (Pawn)->GetVelocity() * DeltaTime, Pawn->GetLocation().y);
	dynamic_cast<AFirstPlayer*> (Pawn)->SetCollider();
	dynamic_cast<AFirstPlayer*> (Pawn)->SetDirection(EDirection::ERight);
	if (dynamic_cast<AFirstPlayer*> (Pawn)->IsColliding())
	{
		Pawn->SetLocation(PawnLocation);
		dynamic_cast<AFirstPlayer*> (Pawn)->SetCollider();
	}
}

void AFirstPlayerController::MoveDown(const float& DeltaTime)
{
	sf::Vector2f PawnLocation = Pawn->GetLocation();
	Pawn->SetLocation(Pawn->GetLocation().x, Pawn->GetLocation().y + dynamic_cast<AFirstPlayer*> (Pawn)->GetVelocity() * DeltaTime);
	dynamic_cast<AFirstPlayer*> (Pawn)->SetCollider();
	dynamic_cast<AFirstPlayer*> (Pawn)->SetDirection(EDirection::EDown);
	if (dynamic_cast<AFirstPlayer*> (Pawn)->IsColliding())
	{
		Pawn->SetLocation(PawnLocation);
		dynamic_cast<AFirstPlayer*> (Pawn)->SetCollider();
	}
}

void AFirstPlayerController::MoveUp(const float& DeltaTime)
{
	sf::Vector2f PawnLocation = Pawn->GetLocation();
	Pawn->SetLocation(Pawn->GetLocation().x, Pawn->GetLocation().y - dynamic_cast<AFirstPlayer*> (Pawn)->GetVelocity() * DeltaTime);
	dynamic_cast<AFirstPlayer*> (Pawn)->SetCollider();
	dynamic_cast<AFirstPlayer*> (Pawn)->SetDirection(EDirection::EUp);
	if (dynamic_cast<AFirstPlayer*> (Pawn)->IsColliding())
	{
		Pawn->SetLocation(PawnLocation);
		dynamic_cast<AFirstPlayer*> (Pawn)->SetCollider();
	}
}

void AFirstPlayerController::Plant()
{
	unsigned BombDisplacement = 8u; //Variable to centre the bomb on a tile
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
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

AFirstPlayer::AFirstPlayer() : APawn(new AFirstPlayerController)
{
	GGame::Instantiate().GetLevel()->AddActor(this);
	Sprite.setTexture(*(TTextureManager::Get("BombermanFront")));
	Sprite.setOrigin(32, 96);
	SetCollider();
}

void AFirstPlayer::SetCollider()
{
	this->Collider = sf::FloatRect(sf::Vector2f(this->GetLocation().x - 16, this->GetLocation().y - 16), sf::Vector2f(40, 40));
}

void AFirstPlayer::Draw()
{
	GGame::Instantiate().GetWindow().draw(Sprite);
}

void AFirstPlayer::Update(const float & DeltaTime)
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

bool AFirstPlayer::IsColliding()
{
	auto Tiles = GGame::Instantiate().GetLevel()->GetCollidableTiles();
	for (auto Tile : Tiles)
	{
		if (Tile)
		{
			if (this->GetCollider().intersects(dynamic_cast<ATile*> (Tile)->GetCollider()))
			{
				return true;
			}
		}
	}
	return false;
}

bool AFirstPlayer::IsOverlappingSpeedUp()
{
	const float MaxVelocity = 350.f;
	auto Speedups = GGame::Instantiate().GetLevel()->GetSpeedUps();
	for (auto Speedup : Speedups)
	{
		auto TempSpeedup = dynamic_cast<ASpeedUp*> (Speedup);
		if (TempSpeedup)
		{
			if (this->GetCollider().intersects(TempSpeedup->GetCollider()))
			{
				GGame::Instantiate().GetLevel()->RemoveActor(Speedup);
				if (Velocity < MaxVelocity)
				{
					Velocity += 20;
				}
				return true;
			}
		}
	}
	return false;
}

bool AFirstPlayer::IsDead()
{
	auto Explosions = GGame::Instantiate().GetLevel()->GetExplosions();
	for (auto Explosion : Explosions)
	{
		if (Explosion)
		{
			if (this->GetCollider().intersects(dynamic_cast<AExplosion*> (Explosion)->GetCollider()))
			{
				return true;
			}
		}
	}
	return false;
}