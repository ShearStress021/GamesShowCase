#include "gameScene.hpp"



namespace dominion {

	GameScene::GameScene(TextureHandler& texture) :
		texHandler(texture), player(texHandler.getTexture("hero"))
	{

	}

	void GameScene::render() const {
		DrawRectangle(200, 300,100,200,YELLOW);
	}

	Next GameScene::update(float dt){
		return {};
	}


}
