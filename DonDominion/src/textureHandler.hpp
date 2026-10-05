#pragma once
#include "helpers.hpp"
#include <unordered_map>
#include <string>
#include <filesystem>


namespace dominion {
	class TextureHandler {
		private:
			Texture2D texFallback{};
			std::unordered_map<std::string, Texture> textures{};
		public:
			TextureHandler(){
				Image img = GenImageChecked(8,8,2,2,MAGENTA,BLACK);
				texFallback = LoadTextureFromImage(img);
				UnloadImage(img);

			}

			~TextureHandler(){
				for(auto& [name, tex]: textures) if(tex.id != texFallback.id) UnloadTexture(tex);
				UnloadTexture(texFallback);
			}

			const Texture2D& loadTexture(const std::string& name, const std::string& path){
				if(auto it = textures.find(name); it != textures.end()) return it->second;
				Texture2D tex = LoadTexture(path.c_str());
				if(tex.id == 0) tex = texFallback;
				return textures.emplace(name,tex).first->second;
			}

			const Texture2D& getTexture(const std::string& name) const{
				auto it = textures.find(name);
				return it != textures.end() ? it->second : texFallback;
			}

			void loadTexures() {
				std::filesystem::create_directories("data/sprites");
				for(const auto& file: std::filesystem::recursive_directory_iterator("data/sprites")){
					const double budgetTime{0.0008};
					const double startTime{GetTime()};
					while((GetTime() - startTime) < budgetTime){
						if(file.is_regular_file()){
							loadTexture(file.path().stem().string(),file.path().string());
						}
					}
				}

			}

	};

}
