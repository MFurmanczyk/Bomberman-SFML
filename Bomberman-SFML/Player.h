#pragma once
#include "Pawn.h"
#include "Game.h"
#include "Dynamite.h"
#include "Explosion.h"
#include "TextureManager.h"

enum class EDirection
{
	EUp,
	EDown,
	ERight,
	ELeft
};

class APlayerController : public APawnController
{
public:
	APlayerController() : APawnController() {};
	virtual void Update(const float& DeltaTime) override;

private:
	void Move(const float& DeltaTime);
	void MoveLeft(const float& DeltaTime);
	void MoveRight(const float& DeltaTime);
	void MoveDown(const float& DeltaTime);
	void MoveUp(const float& DeltaTime);
	void Plant();

private:
	AActor* Dynamite = nullptr;
	AActor* Explsion[3][3] = { nullptr };
	bool Setter = false;
	float Velocity = 100.f;
};

class APlayer final : public APawn
{
public:
	APlayer();
	virtual void Draw() override;
	virtual void Update(const float& DeltaTime) override;
	inline virtual EDirection GetDirection() const { return this->Direction; };
	inline virtual void SetDirection(EDirection _Direction) { this->Direction = _Direction; };
	inline virtual sf::FloatRect GetCollider() const { return this->Collider; };
	bool IsColliding();

private:
	EDirection Direction;
	sf::FloatRect Collider;
};


