#pragma once
#include <string>
#include <unordered_map>
#include "raylib.h"
#include <filesystem>


namespace dominion {
	class ResourceManager 
	{
		std::unordered_map<std::string, Texture> textures;
		
		Texture& getFallbackTexture();
		

		public:
			ResourceManager() = default;
			~ResourceManager() = default;

			static ResourceManager& get()
			{
				static ResourceManager resourceManager;
				return resourceManager;
			}

			Texture& loadTexture(const std::string& name, const std::filesystem::path& path);

			void loadTextures();

			Texture& getTexture(const std::string& name);

			bool textureExists(const std::string& name);
			
		
	};

}
