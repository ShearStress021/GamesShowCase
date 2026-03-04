#include "heroScene.hpp"



namespace game
{
	HeroScene::HeroScene(){}

	HeroScene::~HeroScene(){}

	void HeroScene::loadGameResources()
	{
		std::shared_ptr<Hero> hero = std::make_shared<Hero>();
		int sceneWidth = GetScreenWidth();

		hero->position = Vector2{sceneWidth/2.f, groundYPos/1.f};

		actors.emplace_back(hero);
	}
}
