#include "Game.h"

GGame::GGame() :
	Window(sf::VideoMode(800u, 600u, 32u), "Bomberman"),
	CurrentState(EState::Initializing),
	Level(new GLevel),
	FrameLimit(60u)
{
	TTextureManager::Load("BombermanFront", "Bomberman/Front/Bman_F_f00.png");
	TTextureManager::Load("BombermanSide", "Bomberman/Side/Bman_F_f00.png");
	TTextureManager::Load("BombermanBack", "Bomberman/Back/Bman_B_f00.png");
	Window.setFramerateLimit(FrameLimit);
	return;
}

GGame::~GGame()
{
	if (Window.isOpen())
	{
		Window.close();
	}
	return;
}

void GGame::Run()
{
	CurrentState = EState::Running;
	sf::Clock Clock;
	auto bman = new APlayer(); //TODO
	float DeltaTime = 1 / 60.f; //Frame duration
	while (CurrentState != EState::Ended)
	{
		float FrameStart = Clock.getElapsedTime().asSeconds();
		sf::Event Event;
		Quit(Event);
		Window.clear();
		Level->Update(DeltaTime);
		Level->Draw();
		Window.display();
		DeltaTime = Clock.getElapsedTime().asSeconds() - FrameStart; //Why this? Why this? Oh doughter of the sea? XD
	}
	return; 
}

void Quit(sf::Event &Event)
{
	auto& Game = GGame::Instantiate();
	while (Game.GetWindow().pollEvent(Event))
	{	
		if (Event.type == sf::Event::Closed)
		{
			Game.SetState(EState::Ended);
		}
	}
}
