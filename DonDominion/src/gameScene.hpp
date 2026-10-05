#pragma once
#include "textureHandler.hpp"
#include "hero.hpp"



namespace dominion{

	class GameScene {
		public:
			explicit GameScene(TextureHandler& texH);
			Next update(float dt);
			void render() const;
		private:
			TextureHandler& texHandler;
			Player player;




	};

}
