#pragma once

#include <iostream>
#include "EngineCore.h"
#include "Level.h"
#include "Player.h"
#include "TextureManager.h"
#include "Tile.h"
enum class EState
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
	void Initialize();
public:
	void Run(); //Runs main game's code
	inline void SetState(EState _pState) { CurrentState = _pState; }
	inline EState GetState() const { return this->CurrentState; }
	inline std::shared_ptr<GLevel> GetLevel() { return this->Level; }
	inline sf::RenderWindow& GetWindow() { return this->Window; }

private:
	unsigned FrameLimit;
	EState CurrentState;	
	sf::RenderWindow Window;			// Application's window.
	std::shared_ptr<GLevel> Level;		// Current level
};

void Quit(sf::Event &Event);
