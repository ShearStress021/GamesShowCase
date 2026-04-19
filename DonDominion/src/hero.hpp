#pragma once
#include "resourceManager.hpp"
#include "animation.hpp"
#include "map.hpp"


namespace dominion {


	class Hero {
		public:
			Hero();
			~Hero();

			void render();
			void makeAnimation();
			void updatePlayer(Map& map);
			void updateMovement();

			
			Vector2 getCenter();
		    Rectangle getBounds() const;
			Vector2 pos,vel, prev;





		private:
			//Animation anim{};
			Texture2D* texture{&getTexture("hero")};
			Rectangle frameRect{};
			float width{};
			float height{};
			int  maxFrames{};
			int frame{};
			float runningTime{};
			float updateTime{1/18.f};
			bool onGround = false;

			void applyGravity();
			void resolveCollision(Map& map);



	};

}
