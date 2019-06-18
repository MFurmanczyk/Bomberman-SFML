#include "TextureManager.h"
#include <exception>

TTextureManager::~TTextureManager()
{
	for (auto Texture : Textures)
	{
		delete (Texture.second);
	}
}

sf::Texture * TTextureManager::Load(const std::string & _TextureName, const std::string & _TexturePath)
{
	sf::Texture* Texture = nullptr;
	Texture = TTextureManager::Get(_TextureName);

	//if exists
	if (Texture)
	{
		Texture->loadFromFile(_TexturePath);
	}
	else
	{
		Texture = new sf::Texture();
		if (Texture->loadFromFile(_TexturePath))
		{
			TTextureManager::Instantiate().Textures[_TextureName] = Texture;
		}
		else
		{
			throw std::invalid_argument(_TexturePath);
		}
		
	}

	return Texture;
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
