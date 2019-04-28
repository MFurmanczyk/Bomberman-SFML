#pragma once
#include <iostream>
#include "EngineCore.h"
#include "Level.h"

//Singleton pattern Game class
class GGame final
{
public:
	~GGame();
	GGame(const GGame &) = delete;
	void operator=(const GGame &) = delete;
	inline static GGame& Instantiate()
	{
		static GGame Instance;
		return Instance;
	}
private:
	GGame();
public:
	enum class State
	{
		Initializing,
		Running,
		Paused,
		Ended
	};
	void Run(); //Runs main game's code
	inline State GetState() const { return this->CurrentState; }
	inline sf::RenderWindow& GetWindow() { return this->Window; }

private:
	unsigned FrameLimit;
	State CurrentState;	
	sf::RenderWindow Window;			// Application's window.
	std::unique_ptr<GLevel> Level;		// Current level
};
