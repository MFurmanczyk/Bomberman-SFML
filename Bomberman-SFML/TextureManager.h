#pragma once
#include "EngineCore.h"
#include <unordered_map>

class TTextureManager final
{

public:
	TTextureManager(const TTextureManager& _Other) = delete;
	void operator= (const TTextureManager& _Other) = delete;
	typedef std::unordered_map<std::string, sf::Texture*> TTextures;

	~TTextureManager();

	static sf::Texture* Load(const std::string& _TextureName, const std::string& _TexturePath);
	static bool Unload(const std::string& _TextureName);
	static sf::Texture* Get(const std::string& _TextureName);	
	inline static bool Exists(const std::string& _TextureName) { return TTextureManager::Get(_TextureName) != nullptr; }
	
	void Cleanup();

private:
	TTextureManager() = default;
	inline static TTextureManager& Instantiate()
	{
		static TTextureManager Instance;
		return Instance;
	};

private:
	TTextures Textures;
};
