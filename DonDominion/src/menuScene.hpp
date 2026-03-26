#pragma once

#include "scene.hpp"
#include "hero.hpp"
#include "raylib.h"
#include "background.hpp"

namespace dominion {

	class MenuScene : public Scene {
		enum class Phase{FADEIN, LOAD, FADEOUT};
		Phase phase = Phase::FADEIN;
		float alpha{1.f};
		float fadeTimer{};
		Hero hero{};
		const Texture &backGround{getTexture("back")};
		const Texture &foreGround{getTexture("ground")};


		public:
			MenuScene() = default;
			~MenuScene() = default;

			static ScenePtr make()
			{
				return std::make_unique<MenuScene>();
			}

			void update() override;
			void render() override;
			void change(Scenes& scenes) override;

			void updateFadeIn();
			void updateLoading();
			void updateFadeOut();

	};

	
}

