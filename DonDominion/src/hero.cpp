#include "hero.hpp"



namespace dominion {

	Hero::Hero(){
		maxFrames = 6;

		width = texture.width*1.f/ maxFrames;
		height = texture.height;
		frameRect = {0.f,0.f, (float)width, (float)height};
		


	}

	Hero::~Hero(){
		UnloadTexture(texture);

	}

	void Hero::render(float deltaTime)
	{
		heroAnimate(deltaTime);
		//Texture2D &texture = getTexture("hero");
	//	Rectangle source{texture.width/8.f * frame,0.f, texture.width/8.f, texture.height/1.f};
		Rectangle dest{GetScreenWidth()/4.f, GetRenderHeight()/2.f,width * 2.f ,height *2.f };
		DrawTexturePro(texture,frameRect,dest,Vector2{},0.f,WHITE);

	}

	void Hero::heroAnimate(float deltaTime){
		runningTime += deltaTime;
		if (runningTime > updateTime){
			++frame;
			runningTime = 0.f;
			frame %= maxFrames;

			frameRect.x = (float) width * frame;

		}

	}



}
