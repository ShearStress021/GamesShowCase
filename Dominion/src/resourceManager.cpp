#include "resourceManager.hpp"
#include <filesystem> 



namespace dominion {

	Texture2D& loadTexture(const std::string &name, const std::string &path)
	{
	  if (textures.count(name)) {
			 return textures[name];
	  }

	  Texture texture = LoadTexture(path.c_str());
	  if (texture.id == 0) {
		 
		   return getFallbackTexture();
	  }
	  textures.insert({name, texture});
	  return textures[name];

	}
	Texture& getTexture(const std::string &name)
	{
	  if (!textures.count(name)) {
///			
	 		return getFallbackTexture();
	  }
	  return textures[name];

	}
	
	void loadTextures()
	{
	  std::filesystem::create_directories("data/sprites/");
	  for (const auto &file: std::filesystem::recursive_directory_iterator("data/sprites/")) {
		if (file.is_regular_file()) {
				 loadTexture(file.path().stem().string(), file.path().string());
		  }
	  }

	}

	Texture& getFallbackTexture()
	{
		static Texture fallbackTexture;
		static bool loaded = false;

		if (!loaded) {
			  Image image = GenImageChecked(8, 8, 2, 2, MAGENTA, BLACK);
			  fallbackTexture = LoadTextureFromImage(image);
			  UnloadImage(image);
			  loaded = true;
		}
		return fallbackTexture;

	}
}

