#include "startScene.hpp"



namespace dominion {
	StartScene::StartScene(TextureHandler& textures) :
		tex(textures),
		loadIcon(&tex.loadTexture("loading", "data/sprites/loading.png"))
	{
	}


	void StartScene::render() const {
		const auto& load = tex.getTexture("loading");
		const float w = load.width, h = load.height;
		const float sx = GetScreenWidth() / 2.f, sy = GetScreenHeight() / 2.f;
		const float barW{300.f};


		DrawTexturePro(load, {0.f, 0.f, w, h}, {sx , sy ,w * 2.f,  h * 2.f}, {w, h}, rotation, BLUE);
		DrawRectangleLines(int(sx - barW/2), int(sy + h * 2), int(barW), 10,GRAY);
		

	}

	Next StartScene::update(float dt){
		change(dt);
		if(fadeOut) return SceneId::Game;
		return {};

	}

	void StartScene::change(float dt) {

		rotation += dt * 360;
		timer += dt;
		fadeOut = (timer > 5.f);
		tex.loadTexures();
	}


}
