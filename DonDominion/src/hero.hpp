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

			
			Vector2 getCenter();
		    Rectangle getBounds();





		private:
			//Animation anim{};
			Texture2D* texture{&getTexture("hero")};
			Vector2 pos,vel, prev;
			Rectangle frameRect{};
			float width{};
			float height{};
			int  maxFrames{};
			int frame{};
			float runningTime{};
			float updateTime{1/18.f};


	};

}
