#include "gameScene.hpp"
#include "baseActor.hpp"




namespace game 
{
	GameScene::GameScene() 
	{
		int sceneHeight = GetScreenHeight();

		groundYPos = (3 * sceneHeight) / 4;

	
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
		if(actors.size())
		{
			for (auto &actor : actors)
			{
				actor->draw();
			}
		}
	}
}
