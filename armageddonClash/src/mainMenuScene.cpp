#include "mainMenuScene.hpp"
#include "heroScene.hpp"



namespace game 
{
	MainMenuScene::MainMenuScene(){
		startClicked = false;
	}
	MainMenuScene::~MainMenuScene(){}


	void MainMenuScene::draw()
	{
		GameScene::draw();

		DrawText("There You are", 10,10,20,RED);

	}

	void MainMenuScene::loadGameResources()
	{
		std::shared_ptr<Hero> hero = std::make_shared<Hero>();
		int sceneWidth = GetScreenWidth();
		int sceneHeight = GetScreenHeight();

		hero->position = Vector2{sceneWidth/2.f, sceneHeight/2.f};



		actors.emplace_back(hero);

	}

	std::shared_ptr<GameScene> MainMenuScene::update()
	{
		return std::shared_ptr<HeroScene>();

	}
}
