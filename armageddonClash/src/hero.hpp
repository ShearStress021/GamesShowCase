#pragma once

#include "baseActor.hpp"
#include "raylib.hpp"
#include "rectangle.hpp"
#include "raymath.hpp"
#include <iostream>



namespace game {

	class Hero : public BaseActor{

		public:
			Hero();

			virtual void update();
			virtual void draw();
			virtual Rectangle getBoundingBox();

			virtual ~Hero();


		private:
			Vector2 getUpperLeftPosition();
			Texture2D texture{};
			unsigned numFrames{};
			int frameWidth{};
			float frameDelay{};
			float frameDelayCounter{};
			unsigned frameIndex{};
			Rectangle frameRect{};
			bool isOnGround{};



	};

}
