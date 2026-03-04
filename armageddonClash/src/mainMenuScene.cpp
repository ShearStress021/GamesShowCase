#include "mainMenuScene.hpp"
#include "heroScene.hpp"



namespace game 
{
	MainMenuScene::MainMenuScene(){}
	MainMenuScene::~MainMenuScene(){}


	void MainMenuScene::draw()
	{
		GameScene::draw();

		DrawText("There You are", 10,10,20,RED);

	}
}
