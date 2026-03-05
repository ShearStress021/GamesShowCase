#include "gameScene.hpp"
#include "baseActor.hpp"
#include "mainMenuScene.hpp"




namespace game 
{
	GameScene::GameScene() 
	{
//		loadGameResources();
		int sceneHeight = GetScreenHeight();

		groundYPos = (sceneHeight) / 4;

	
	}

	GameScene::~GameScene()
	{
		freeGameResources();
	}


	void GameScene::freeGameResources()
	{
		actors.clear();
	}

	void GameScene::loadGameResources()
	{

	}

	void GameScene::draw()
	{

		ClearBackground(WHITE);
		if(actors.size())
		{
			for (auto &actor : actors)
			{
				actor->draw();
			}
		}
	}

	std::shared_ptr<GameScene> GameScene::update()
	{
		for(auto &actor : actors)
		{
			actor->update();
		}
		return std::make_shared<MainMenuScene>();
	}

	void GameScene::start()
	{

	}
}
