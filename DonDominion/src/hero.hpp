#pragma once
#include "raylib.h"
#include "resource.hpp"


namespace dominion {
	class Hero {
		private:
			Texture2D& texture{getTexture("hero")};
			unsigned maxFrames{};
			unsigned frame{};
			float runningTime{};
			float updateTime{1/12.f};
			Rectangle frameRect{};
			float width{};
			float height{};

		public:
			~Hero();
			Hero();
			void render(float deltaTime);
			void heroAnimate(float deltaTime);



	};
}
