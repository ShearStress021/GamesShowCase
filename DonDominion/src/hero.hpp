#pragma once
#include "resourceManager.hpp"
#include "animation.hpp"
#include "map.hpp"


namespace dominion {

	struct Bullet {
		Vector2 pos;
		Vector2 vel;
		bool active;
	};

	enum class HeroState {idle,walk,jumping, running, shot};
	class Hero {
		public:
			Hero();
			~Hero();

			void render();
			void makeAnimation(float deltaTime);
			void updatePlayer(Map& map);
			void updateMovement(float deltaTime);

			
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
			float updateTime{1/12.f};
			bool onGround = false;

			void applyGravity();
			void resolveCollision(Map& map);
			void updateBullets(float deltaTime);
			HeroState state;
			float leftRight{-1.f};
			std::vector<Bullet> bullets;
			float bulletSpeed{};



	};

}
