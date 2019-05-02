#include "../Core/Pawn.h"


enum class PlayerDirection
{
	EUp,
	EDown,
	ELeft, 
	ERight
};

class APlayerController : public APawnController
{
public:
	APlayerController() : APawnController() {};
	virtual void Update(const float& DeltaTime) override;
};

class APlayer final : public APawn
{
public:
	APlayer() : APawn(new APlayerController) {};
public:
	virtual void Draw() override;
};

