#pragma once 
#include "hero.hpp"
#include "scene.hpp"
#include "menuScene.hpp"
#include "map.hpp"
#include "resourceManager.hpp"
#include "utils.hpp"



namespace dominion {

	class GameScene : public Scene {
		public:
			GameScene();
			~GameScene();

			void update() override;
			void render() override;
			void fixedUpdate() override;
			void updateControls();
			void updateEnviroment();

			std::shared_ptr<Scene> change() override;

//			Hero hero{};
		private:
			Map map;
			Hero hero;
			Camera2D camera{0};

		   const Texture &backGround{getTexture("back")};
		   const Texture &foreGround{getTexture("ground")};

	};

}

