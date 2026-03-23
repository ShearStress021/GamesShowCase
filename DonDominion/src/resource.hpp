#pragma once

#include "raylib.h"
#include <string>
#include <unordered_map>



namespace dominion {
	
	
		static std::unordered_map<std::string,Texture> textures;
	

		Texture& loadTexture(const std::string &name, const std::string &path);
		void loadTextures();
		Texture& getTexture(const std::string &name);
		Texture& getFallbackTexture();


}