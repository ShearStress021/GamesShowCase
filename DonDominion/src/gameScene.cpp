#include "gameScene.hpp"
#include "random.hpp"
#include "background.hpp"



namespace dominion {

	static int index = 0;


	static const char* blockMap[] {
		"air","grass", "panel","dirt", "ground", "brick"
	};
	static int size = 6;


	GameScene::GameScene() {


		camera.zoom = 1.f;
		camera.target = hero.pos;
		camera.offset = getScreenCenter();
		camera.rotation = 0.0f;

	}
	GameScene::~GameScene() {

	}

	void GameScene::render() {
	 drawBackGround(backGround, foreGround, 0.0001f, 0.0002f, 0.002f);
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
//		 Rectangle b      = hero.getBounds();
		 //camera.target    = { b.x + b.width / 2.f, b.y + b.height / 2.f };

//		camera.target = lerp(camera.target, hero.getCenter(), 25.f*GetFrameTime());

	

	}


}
