#include "gameScene.hpp"
#include "random.hpp"



namespace dominion {

	static int index = 0;


	static const char* blockMap[] {
		"air","grass", "panel","dirt", "ground", "brick"
	};
	static int size = 6;


	GameScene::GameScene() {

		camera.zoom = 1.f;
//		camera.target = hero.getCenter();
//		camera.offset = getScreenCenter();

	}
	GameScene::~GameScene() {

	}

	void GameScene::render() {
		BeginMode2D(camera);

		map.render();
		hero.render();
		EndMode2D();

	//	drawTexture(getTexture(blockMap[index]), {GetScreenWidth() - 75.f, GetScreenHeight() - 75.f}, {50.f, 50.f}, 0.f,WHITE);
		
	}

	void GameScene::fixedUpdate() {

//		hero.updatePlayer(GetFrameTime());
		

	}

	std::shared_ptr<Scene> GameScene::change() {
		return std::make_shared<MenuScene>();
	}

	void GameScene::update() {
		updateControls();
//		updateEnviroment();
	}

	void GameScene::updateControls(){
		hero.updatePlayer(map);

//		camera.target = lerp(camera.target, hero.getCenter(), 25.f*GetFrameTime());

	

	}


}
