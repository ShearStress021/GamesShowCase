#include "startScene.hpp"
#include "resourceManager.hpp"
#include "menuScene.hpp"
#include <iostream>




namespace dominion {

	namespace
	{
		constexpr float fadeTime{.5f};
		constexpr float waitTime{.5f};

	}

	StartScene::StartScene()
	{
		loadTexture("loading", "data/sprites/loading.png");

//		loadTextures();

	}
	void StartScene::fixedUpdate() {

	}

	void StartScene::update()
	{

		rotation += dt * 360.f;
		if (loadPhase == Load::textures){
			loadTextures();
			loadPhase = Load::count;
		}
		else if(loadPhase == Load::count) {
			finalFadeTimer += realDt;
			fadingOut = (finalFadeTimer >= 1.f);
			

		}
	}


	std::shared_ptr<Scene> StartScene::change()
	{
		return std::make_shared<MenuScene>();

	}




	void StartScene::render()
	{
		BeginDrawing();
			ClearBackground(BLACK);
			  auto& tex = getTexture("loading");

			  DrawTexturePro(tex, {0.f, 0.f, (float)tex.width, (float)tex.height}, {GetScreenWidth() / 2.f, GetScreenHeight() / 2.f,
					  tex.width * 2.f, tex.height * 2.f}, {(float)tex.width, (float)tex.height}, rotation, WHITE);
      		  DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Fade(BLACK, alpha));
		EndDrawing();

	}
}

