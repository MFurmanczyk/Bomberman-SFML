#include "SecondPlayer.h"
#include <typeinfo>
#include "Speedup.h"

void ASecondPlayerController::Update(const float & DeltaTime)
{
	auto& Game = GGame::Instantiate();
	Move(DeltaTime);
	Plant();
	if (!Game.GetLevel()->ActorExists(Dynamite))
	{
		Dynamite = nullptr;
		Setter = false;
	}
	dynamic_cast<ASecondPlayer*>(Pawn)->IsOverlappingSpeedUp();
}

void ASecondPlayerController::Move(const float& DeltaTime)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		this->MoveLeft(DeltaTime);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		this->MoveRight(DeltaTime);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		this->MoveDown(DeltaTime);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		this->MoveUp(DeltaTime);
	}
}

void ASecondPlayerController::MoveLeft(const float& DeltaTime)
{
	sf::Vector2f PawnLocation = Pawn->GetLocation();
	Pawn->SetLocation(Pawn->GetLocation().x - dynamic_cast<ASecondPlayer*> (Pawn)->GetVelocity() * DeltaTime, Pawn->GetLocation().y);
	dynamic_cast<ASecondPlayer*> (Pawn)->SetCollider();
	dynamic_cast<ASecondPlayer*> (Pawn)->SetDirection(EDirection::ELeft);
	if (dynamic_cast<ASecondPlayer*> (Pawn)->IsColliding())
	{
		Pawn->SetLocation(PawnLocation);
		dynamic_cast<ASecondPlayer*> (Pawn)->SetCollider();
	}
}

void ASecondPlayerController::MoveRight(const float& DeltaTime)
{
	sf::Vector2f PawnLocation = Pawn->GetLocation();
	Pawn->SetLocation(Pawn->GetLocation().x + dynamic_cast<ASecondPlayer*> (Pawn)->GetVelocity() * DeltaTime, Pawn->GetLocation().y);
	dynamic_cast<ASecondPlayer*> (Pawn)->SetCollider();
	dynamic_cast<ASecondPlayer*> (Pawn)->SetDirection(EDirection::ERight);
	if (dynamic_cast<ASecondPlayer*> (Pawn)->IsColliding())
	{
		Pawn->SetLocation(PawnLocation);
		dynamic_cast<ASecondPlayer*> (Pawn)->SetCollider();
	}
}

void ASecondPlayerController::MoveDown(const float& DeltaTime)
{
	sf::Vector2f PawnLocation = Pawn->GetLocation();
	Pawn->SetLocation(Pawn->GetLocation().x, Pawn->GetLocation().y + dynamic_cast<ASecondPlayer*> (Pawn)->GetVelocity() * DeltaTime);
	dynamic_cast<ASecondPlayer*> (Pawn)->SetCollider();
	dynamic_cast<ASecondPlayer*> (Pawn)->SetDirection(EDirection::EDown);
	if (dynamic_cast<ASecondPlayer*> (Pawn)->IsColliding())
	{
		Pawn->SetLocation(PawnLocation);
		dynamic_cast<ASecondPlayer*> (Pawn)->SetCollider();
	}
}

void ASecondPlayerController::MoveUp(const float& DeltaTime)
{
	sf::Vector2f PawnLocation = Pawn->GetLocation();
	Pawn->SetLocation(Pawn->GetLocation().x, Pawn->GetLocation().y - dynamic_cast<ASecondPlayer*> (Pawn)->GetVelocity() * DeltaTime);
	dynamic_cast<ASecondPlayer*> (Pawn)->SetCollider();
	dynamic_cast<ASecondPlayer*> (Pawn)->SetDirection(EDirection::EUp);
	if (dynamic_cast<ASecondPlayer*> (Pawn)->IsColliding())
	{
		Pawn->SetLocation(PawnLocation);
		dynamic_cast<ASecondPlayer*> (Pawn)->SetCollider();
	}
}

void ASecondPlayerController::Plant()
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

ASecondPlayer::ASecondPlayer() : APawn(new ASecondPlayerController)
{
	GGame::Instantiate().GetLevel()->AddActor(this);
	Sprite.setTexture(*(TTextureManager::Get("BombermanFront")));
	Sprite.setOrigin(32, 96);
	SetCollider();
}

void ASecondPlayer::SetCollider()
{
	this->Collider = sf::FloatRect(sf::Vector2f(this->GetLocation().x - 16, this->GetLocation().y - 16), sf::Vector2f(40, 40));
}

void ASecondPlayer::Draw()
{
	GGame::Instantiate().GetWindow().draw(Sprite);
}

void ASecondPlayer::Update(const float & DeltaTime)
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

bool ASecondPlayer::IsColliding()
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

bool ASecondPlayer::IsOverlappingSpeedUp()
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

bool ASecondPlayer::IsDead()
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