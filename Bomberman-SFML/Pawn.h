#pragma once
#include "Actor.h"


class APawnController;

class APawn : public AActor
{
public:
	APawn(APawnController* _Controller);

	virtual ~APawn() override;

	virtual void Update(const float &DeltaTime) override;

	virtual void Draw() = 0;

	void SetNewController(APawnController* _Controller);

protected:
	APawnController* Controller;

	float Velocity = 200.f;
};

class APawnController
{
public:
	APawnController() = default;
	virtual ~APawnController();

	inline bool IsPossessed() const { return Pawn != nullptr; };

	virtual void Update(const float& DeltaTime) = 0;

	bool Possess(APawn* _Pawn);

protected:
	APawn* Pawn;
};
