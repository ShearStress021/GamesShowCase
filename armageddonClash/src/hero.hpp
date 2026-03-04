#pragma once

#include "baseActor.hpp"
#include "raylib.hpp"
#include "rectangle.hpp"
#include "raymath.hpp"




namespace game {

	class Hero : public BaseActor{

		public:
			Hero();

			virtual bool update(bool onGround);
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



	};

}
