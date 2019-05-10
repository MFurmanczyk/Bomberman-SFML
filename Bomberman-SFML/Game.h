#pragma once

#include <iostream>
#include "EngineCore.h"
#include "Level.h"
#include "Player.h"

enum class State
{
	Initializing,
	Running,
	Paused,
	Ended
};

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
	void Run(); //Runs main game's code
	inline void SetState(State _pState) { CurrentState = _pState; }
	inline State GetState() const { return this->CurrentState; }
	inline sf::RenderWindow& GetWindow() { return this->Window; }

private:
	unsigned FrameLimit;
	State CurrentState;	
	sf::RenderWindow Window;			// Application's window.
	std::unique_ptr<GLevel> Level;		// Current level
};

void Quit(sf::Event &event);
