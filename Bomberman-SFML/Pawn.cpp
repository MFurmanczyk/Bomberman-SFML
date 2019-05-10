#include "Pawn.h"

APawn::APawn(APawnController* _Controller)
{
	if (_Controller)
	{
		this->Controller = _Controller;
	}
	Controller->Possess(this);
}

APawn::~APawn()
{
	delete Controller;
}

void APawn::Update(const float & DeltaTime)
{
	if (Controller)
	{
		this->Controller->Update(DeltaTime);
	}
}

void APawn::SetNewController(APawnController * _Controller)
{
	if (this->Controller)
	{
		if (_Controller)
		{
			delete this->Controller;
			this->Controller = _Controller;
		}
	}
}

APawnController::~APawnController()
{
	if (Pawn)
	{
		delete Pawn;
	}
}

bool APawnController::Possess(APawn* _Pawn)
{
	if (!Pawn)
	{
		if (_Pawn)
		{
			this->Pawn = _Pawn;
			return true;
		}
	}
	return false;
}
