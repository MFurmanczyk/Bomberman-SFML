#include "Game.h"

GGame::GGame() :
	Window(sf::VideoMode(960u, 960u), "Bomberman"),
	CurrentState(EState::Initializing),
	Level(new GLevel),
	FrameLimit(60u)
{
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
	Initialize();
	CurrentState = EState::Running;
	sf::Clock Clock;
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

void GGame::Initialize()
{
	std::ifstream File;
	File.open("Map.txt", std::ios::in);
	TTextureManager::Load("BombermanFront", "Sprites/Bomberman/Front/Bman_F_f00.png");
	TTextureManager::Load("BombermanSide", "Sprites/Bomberman/Side/Bman_F_f00.png");
	TTextureManager::Load("BombermanBack", "Sprites/Bomberman/Back/Bman_B_f00.png");
	TTextureManager::Load("TileGround", "Sprites/Blocks/BackgroundTile.png");
	TTextureManager::Load("TileSolid", "Sprites/Blocks/SolidBlock.png");
	TTextureManager::Load("TileExplodable", "Sprites/Blocks/ExplodableBlock.png");
	TTextureManager::Load("Bomb", "Sprites/Bomb/Bomb_f02.png");
	TTextureManager::Load("Explosion", "Sprites/Flame/Flame_f00.png");

	if (File.is_open())
	{
		unsigned char TileType;
		unsigned int XModifier = 0;
		unsigned int YModifier = 0;
		for (YModifier = 0; YModifier < 15; YModifier++)
		{
			for (XModifier = 0; XModifier < 15; XModifier++)
			{
				File >> TileType;
				if (TileType == '1')
				{
					auto Tile = new ASolidTile();
					Tile->SetLocation(XModifier * 64, YModifier * 64);
					Level->AddActor(Tile);
					dynamic_cast<ASolidTile*>(Tile)->SetCollider(Tile->GetLocation());
				}
				else if (TileType == '2')
				{
					auto Tile = new AExplodableTile();
					auto BackgroundTile = new AGroundTile();
					Tile->SetLocation(XModifier * 64, YModifier * 64);
					BackgroundTile->SetLocation(XModifier * 64, YModifier * 64);
					Level->AddActor(BackgroundTile);
					Level->AddActor(Tile);
					dynamic_cast<AExplodableTile*>(Tile)->SetCollider(Tile->GetLocation());

				}
				else
				{
					auto Tile = new AGroundTile();
					Tile->SetLocation(XModifier * 64, YModifier * 64);
					Level->AddActor(Tile);
				}
			}
		}

	}
	File.close();
	auto bman = new APlayer();
	bman->SetLocation(96, 96);
	bman->SetDirection(EDirection::EDown);
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
