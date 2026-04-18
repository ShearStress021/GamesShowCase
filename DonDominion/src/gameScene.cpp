#include "gameScene.hpp"
#include "random.hpp"




namespace dominion {

	static int index = 0;

	static const char* blockMap[] {
		"grass", "panel","dirt", "ground", "brick"
	};


	GameScene::GameScene() {

		camera.zoom = 1.f;
		camera.target = hero.getCenter();
		camera.offset = getScreenCenter();

	}
	GameScene::~GameScene() {

	}

	void GameScene::render() {
		BeginMode2D(camera);

		map.render(camera);
		hero.render();
		EndMode2D();

		drawTexture(getTexture(blockMap[index]), {GetScreenWidth() - 75.f, GetScreenHeight() - 75.f}, {50.f, 50.f}, 0.f,WHITE);
		
	}

	void GameScene::fixedUpdate() {

//		hero.updatePlayer(GetFrameTime());
		

	}

	std::shared_ptr<Scene> GameScene::change() {
		return std::make_shared<MenuScene>();
	}

	void GameScene::update() {
		updateControls();
		updateEnviroment();
	}

	void GameScene::updateControls(){
		hero.updatePlayer(map);

		camera.target = lerp(camera.target, hero.getCenter(), 25.f*GetFrameTime());

	

	}
	void GameScene::updateEnviroment(){

		for (int y = map.sizeY -1;y >= 0; --y){
			for(int x = map.sizeX -1; x >= 0; --x){
				auto& block = map[y][x];
				
				if(block.type == Block::grass) {
					if(map[y][x].value2 == 0){
						map[y][x].value2 = random(100, 255);
						
					}
					++map[y][x].value;
					if (map[y][x].value >= map[y][x].value2){
						map[y][x].value = 0;
						map.setBlock(x,y,"dirt");
					}
				}


			}
		}
	}

}

