#include "hero.hpp"
#include <iostream>



namespace dominion {
	constexpr Vector2 size {2.f, 3.f};
	constexpr float GRAVITY   = 900.f;

	Hero::Hero(){
		maxFrames = 7;
		vel = {0,0};
		pos = {100.f, 100.f};
		prev = pos;
		width = texture->width*1.f/ maxFrames;
		height = texture->height;
		frameRect = {0.f,0.f, (float)width , (float)height};
		
	}

	Hero::~Hero(){

	}
	void Hero::updatePlayer(Map& map){
		makeAnimation();
		onGround = false;

		applyGravity();
		pos.y += vel.y;
		resolveCollision(map);
		
	}
	void Hero::makeAnimation(){
		runningTime += GetFrameTime();
		if (runningTime > updateTime){
			++frame;
			runningTime = 0.f;
			frame %= maxFrames;

			frameRect.x = (float) width * frame;

		}

	}

	void  Hero::render(){

		Rectangle dest{pos.x, pos.y,width*1.5f, height*1.5f};
		DrawTexturePro(*texture,frameRect,dest,Vector2{},0.f,WHITE);
//		DrawRectangleLinesEx(dest,2.f,RED);


	}
	
	void Hero::resolveCollision(Map &map){
		Rectangle bounds = getBounds();

		// check the 4 corners of the player
		auto check = [&](float cx, float cy) {
			return map.isSolidAtWorld(cx, cy);
		};

		float left   = bounds.x;
		float right  = bounds.x + bounds.width  - 1;
		float top    = bounds.y;
		float bottom = bounds.y + bounds.height - 1;

		// --- vertical collision ---
		if (vel.y > 0) {  // falling
			if (check(left, bottom) || check(right, bottom)) {
				
				float screenH = (float)GetScreenHeight();


				float mapTopY = screenH - (MAP_ROWS * TILE_SIZE);

				int row = (int)((bottom) / TILE_SIZE);
				pos.y   = row * TILE_SIZE - bounds.height;
				//
				//pos.y = mapTopY + (row * TILE_SIZE) - bounds.height;
				vel.y   = 0.f;
				onGround = true;
			}
		} else if (vel.y < 0) {  // jumping
			if (check(left, top) || check(right, top)) {
				int row = (int)(top / TILE_SIZE);
				pos.y   = (row + 1) * TILE_SIZE;
				vel.y   = 0.f;
			}
		}


	}

	Vector2  Hero::getCenter(){
		  return {pos.x + width / 2.f, pos.y + height / 2.f};

	}

	Rectangle Hero::getBounds() const {
		return { pos.x, pos.y, width * 1.5f, height * 1.5f };
	}

	void Hero::applyGravity(){
		vel.y = GRAVITY * GetFrameTime();
	}


}
