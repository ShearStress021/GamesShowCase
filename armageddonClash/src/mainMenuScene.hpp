#pragma once


#include "gameScene.hpp"



namespace game 
{
	class MainMenuScene : public GameScene
	{
		public:
			MainMenuScene();
			virtual ~MainMenuScene();
			virtual void draw();

			virtual void loadGameResources();
			virtual std::shared_ptr<GameScene> update();
		private:
			bool startClicked{};
	};
}
