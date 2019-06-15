#include "TextureManager.h"

TTextureManager::~TTextureManager()
{
	for (auto Texture : Textures)
	{
		delete (Texture.second);
	}
}

sf::Texture * TTextureManager::Load(const std::string & _TextureName, const std::string & _TexturePath)
{
	sf::Texture* Result = nullptr;
	Result = TTextureManager::Get(_TextureName);

	//if exists
	if (Result)
	{
		Result->loadFromFile(_TexturePath);
	}
	else
	{
		Result = new sf::Texture();
		Result->loadFromFile(_TexturePath);
		TTextureManager::Instantiate().Textures[_TextureName] = Result;
	}

	return Result;
}

bool TTextureManager::Unload(const std::string & _TextureName)
{
	auto Texture = TTextureManager::Instantiate().Textures.find(_TextureName);


	if (Texture == TTextureManager::Instantiate().Textures.end())
	{
		return false;
	}
	else
	{
		delete Texture->second;
		TTextureManager::Instantiate().Textures.erase(Texture);
		return true;
	}
}

sf::Texture * TTextureManager::Get(const std::string & _TextureName)
{
	auto Texture = TTextureManager::Instantiate().Textures.find(_TextureName);
	if (Texture == TTextureManager::Instantiate().Textures.end())
	{
		return nullptr;
	}
	else
	{
		return Texture->second;
	}
}

void TTextureManager::Cleanup()
{
	for (auto Texture : TTextureManager::Instantiate().Textures)
	{
		delete (Texture.second);
	}
}
