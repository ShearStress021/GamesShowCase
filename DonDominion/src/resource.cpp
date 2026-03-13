#include "resource.hpp"


namespace dominion {

	Texture& ResourceManager::loadTexture(const std::string& name, const std::filesystem::path& path)
	{
		if(textureExists(name))
		{
			return textures[name];
		
		}

		Texture texture = LoadTexture(path.c_str());

		if(texture.id == 0)
		{
			return getFallbackTexture();
		}

		textures.insert({name, texture});
		return textures[name];

	}

	void ResourceManager::loadTextures()
	{
		for(const auto& file: std::filesystem::recursive_directory_iterator("data/sprites"))
		{
			loadTexture(file.path().stem().string(), file.path());

		}

	}

	Texture& ResourceManager::getTexture(const std::string& name)
	{
		if(!textureExists(name))
		{
			return getFallbackTexture();
		}
		return textures[name];
	}

	bool ResourceManager::textureExists(const std::string& name)
	{
		return textures.count(name);
	}


	Texture& ResourceManager::getFallbackTexture()
	{
		static Texture fallbackTexture;
		static bool loaded = false;
		if(!loaded)
		{
			Image image = GenImageChecked(32, 32, 4, 4, MAROON, BLACK);
			fallbackTexture = LoadTextureFromImage(image);
			UnloadImage(image);
			loaded = true;
		}
		return fallbackTexture;
	}




}
