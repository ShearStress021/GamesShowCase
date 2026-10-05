#include "menuScene.hpp"
#include "gameScene.hpp"
//#include "hero.hpp"



namespace dominion {

	MenuScene::MenuScene() {

	}

	void MenuScene::render() {


	}

	void MenuScene::fixedUpdate(){

	}

	std::shared_ptr<Scene> MenuScene::change() {
		return  std::make_shared<GameScene>();

	}

	void MenuScene::update() {
			fadingOut = true;



	}
}

