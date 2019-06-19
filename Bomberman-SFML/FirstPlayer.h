#pragma once
#include "Pawn.h"
#include "Game.h"
#include "Dynamite.h"
#include "Explosion.h"
#include "TextureManager.h"

class AFirstPlayerController : public APawnController
{
public:
	AFirstPlayerController() : APawnController() {};
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
	bool Setter = false;

};

class AFirstPlayer final : public APawn
{
public:
	AFirstPlayer();
	virtual ~AFirstPlayer() = default;
	void SetCollider();
	virtual void Draw() override;
	virtual void Update(const float& DeltaTime) override;
	inline virtual EDirection GetDirection() const { return this->Direction; };
	inline virtual void SetDirection(EDirection _Direction) { this->Direction = _Direction; };
	inline virtual sf::FloatRect GetCollider() const { return this->Collider; };


	
	bool IsColliding();
	bool IsOverlappingSpeedUp();
	bool IsDead();
	inline float GetVelocity() const { return this->Velocity; };

private:
	EDirection Direction = EDirection::EDown;
	sf::FloatRect Collider;
	float Velocity = 100.f;
};