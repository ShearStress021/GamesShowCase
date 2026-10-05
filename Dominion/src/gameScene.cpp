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

		camera.target = hero.pos;
			// 2. Clamp the Camera X
		// Don't let the camera look further left than half a screen width
		float minX = camera.offset.x / camera.zoom;
		if (camera.target.x < minX) {
			camera.target.x = minX;
		}

		// Optional: Clamp the Camera Y to keep the ground at the bottom
		// This prevents the camera from "looking down" into the void below the dirt
		float maxY = (MAP_ROWS * TILE_SIZE) - (camera.offset.y / camera.zoom);
		if (camera.target.y > maxY) {
			camera.target.y = maxY;
		}



	

	}


}
