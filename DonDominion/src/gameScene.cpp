#include "gameScene.hpp"



namespace dominion {

	GameScene::GameScene(TextureHandler& texture) :
		texHandler(texture), player(texHandler.getTexture("hero"))
	{

	}

	void GameScene::render() const {
		player.render();
//		DrawRectangle(200, 300,100,200,YELLOW);
	}

	Next GameScene::update(float dt){
		player.update(dt);
		return {};
	}


}
