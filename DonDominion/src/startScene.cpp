#include "startScene.hpp"



namespace dominion {
	StartScene::StartScene(TextureHandler& textures) :
		tex(textures),
		loadIcon(&tex.loadTexture("loading", "data/sprites/loading.png"))
	{
	}


	void StartScene::render() const {
		const auto& load = tex.getTexture("loading");

		DrawTexturePro(load, {0.f, 0.f, (float)load.width, (float)load.height}, {GetScreenWidth() / 2.f, GetScreenHeight() / 2.f,
				  					  load.width * 2.f, load.height * 2.f}, {(float)load.width, (float)load.height}, rotation, WHITE);
		

	}

	Next StartScene::update(float dt){
		change(dt);
		if(fadeOut) return SceneId::Quit;
		return {};

	}

	void StartScene::change(float dt) {

		rotation += dt * 360;
		timer += dt;
		fadeOut = (timer > 5.f);
		tex.loadTexures();
	}


}
