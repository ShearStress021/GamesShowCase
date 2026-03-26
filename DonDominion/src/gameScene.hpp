#pragma once
#include "scene.hpp"
#include "raylib.h"
#include "resource.hpp"



namespace dominion {

	class GameScene : public Scene 
	{
		enum class Phase {FADEIN, LOAD, FADEOUT};
		Phase phase = Phase::FADEIN;
		float fadeTimer{};
		float wideTimer{};
		float alpha{1.f};
		float rotation{};
		const Texture &backGround{getTexture("back")};
		const Texture &foreGround{getTexture("front")};
		public:
			GameScene();
			~GameScene() = default;
			void render() override;

			static ScenePtr make()
			{
				return std::make_unique<GameScene>();
			}

			void update() override;
			void change(Scenes& scenes) override;
			void updateLoading();
			void updateFadeIn();
			void updateFadeOut();

	};


}
