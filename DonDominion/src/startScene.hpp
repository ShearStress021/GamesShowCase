#pragma once


#include "helpers.hpp"
#include "textureHandler.hpp"


namespace dominion {
	
	class StartScene {
		public:
			explicit StartScene(TextureHandler& textures);
			void change(float dt);
			void render() const;
			Next update(float dt);
			StartScene();
			
			
		private:
			enum class Load{textures, count};
			Load loadPhase = Load::textures;
			float timer{0.f};
			float finalFadeTimer{0.f};
			float rotation{};
			bool fadeOut{false};
			TextureHandler& tex;
			const Texture2D *loadIcon;



	};

}




