#include "hero.hpp"
#include <iostream>



namespace dominion {
	constexpr Vector2 size {2.f, 3.f};

	Hero::Hero(){
		maxFrames = 7;
		vel = {0,0};
//		pos = {GetScreenWidth()/4.f, GetScreenHeight()/2.f};
		prev = pos;
		width = texture->width*1.f/ maxFrames;
		height = texture->height;
		frameRect = {0.f,0.f, (float)width , (float)height};
		
	}

	Hero::~Hero(){

	}
	void Hero::updatePlayer(Map& map){
		makeAnimation();
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


	}

	Vector2  Hero::getCenter(){
		  return {pos.x + width / 2.f, pos.y + height / 2.f};

	}


}
