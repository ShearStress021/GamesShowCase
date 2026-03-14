#include "gameScene.hpp"
#include "menuScene.hpp"
#include "resource.hpp"
#include <csetjmp>
#include <iostream>



namespace dominion 
{
	namespace 
	{
		constexpr float fadeTime{.5f};
		constexpr float waitTime{.5f};

	}

	GameScene::GameScene()
	{
		ResourceManager::get().loadTexture("loading", "data/sprites/loading.png");

	}

	void GameScene::update()
	{
		rotation += GetFrameTime() * 360.f;
		switch(phase)
		{
			case Phase::FADEIN: updateFadeIn(); break;
			case Phase::LOAD:  updateLoading(); break;
			case Phase::FADEOUT: updateFadeOut(); break;

		}
	}


	void GameScene::change(Scenes& scenes)
	{
		scenes.push_back(MenuScene::make());

	}

	void GameScene::updateFadeIn()
	{
		fadeTimer += GetFrameTime();

		alpha = 1.f - fadeTimer / fadeTime;
		if (fadeTimer >= fadeTime)
		{
			fadeTimer = alpha = 0.f;
			phase = Phase::LOAD;
		}
	}


	void GameScene::updateFadeOut()
	{
		wideTimer += GetFrameTime();
		if(wideTimer < waitTime)
		{
			return ;
		}

		fadeTimer += GetFrameTime();
		alpha  = fadeTimer / fadeTime;

		if(fadeTimer >= fadeTime)
		{
			alpha = 1.f;
			quitScene = true;
		}


	}



	void GameScene::updateLoading()
	{
		ResourceManager::get().loadTextures();
		phase = Phase::FADEOUT;
	}

	void GameScene::render()
	{
		BeginDrawing();
			ClearBackground(BLACK);
			  auto& tex = ResourceManager::get().getTexture("loading");

			  DrawTexturePro(tex, {0.f, 0.f, (float)tex.width, (float)tex.height}, {GetScreenWidth() / 2.f, GetScreenHeight() / 2.f, 
					  tex.width * 2.f, tex.height * 2.f}, {(float)tex.width, (float)tex.height}, rotation, WHITE);
      		  DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Fade(BLACK, alpha));
		EndDrawing();
		
	}
		
		

}
