#include "menuScene.hpp"


namespace dominion {
	namespace {
		constexpr float fadeTime{0.25f};
	}

	void MenuScene::update()
	{
		switch(phase)
		{
			case Phase::FADEIN: updateFadeIn(); break;
			case Phase::LOAD: updateLoading(); break;
			case Phase::FADEOUT: updateFadeOut(); break;
		}

	}

	void MenuScene::updateFadeIn()
	{
	   fadeTimer += GetFrameTime();
	   alpha = 1.f - fadeTimer / fadeTime;

	   if (fadeTimer >= fadeTime) {
		  fadeTimer = alpha = 0.f;
		  phase = Phase::LOAD;
	   }

	}

	void MenuScene::updateFadeOut()
	{
	   fadeTimer += GetFrameTime();
	   alpha = fadeTimer / fadeTime;

	   if (fadeTimer >= fadeTime) {
		  alpha = 1.f;
		  quitScene = true;
	   }

	}
	
	void MenuScene::updateLoading()
	{

	}

	void MenuScene::render()
	{
		BeginDrawing();
			ClearBackground(BLACK);
	//		DrawText("lalaladidada", 50, 50, 200, RED);
	//
			drawBackGround(backGround, foreGround, 0.001f, 0.002f,0.2f);
			hero.render(GetFrameTime());
//			DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Fade(BLACK, alpha));
		EndDrawing();

	}

	void MenuScene::change(Scenes& scenes)
	{

	}

}
