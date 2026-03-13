#pragma once

#include "scene.hpp"
#include "raylib.h"

namespace dominion {

	class MenuScene : public Scene {
		enum class Phase{FADEIN, LOAD, FADEOUT};
		Phase phase = Phase::FADEIN;
		float alpha{1.f};
		float fadeTimer{};


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

