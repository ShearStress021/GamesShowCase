#include "hero.hpp"
#include "resource.hpp"
#include <map>



namespace dominion {

	Hero::Hero(){
		maxFrames = 14;

		width = texture->width*1.f/ maxFrames;
		height = texture->height;
		frameRect = {0.f,0.f, (float)width , (float)height};
		


	}

	Hero::~Hero(){
		UnloadTexture(*texture);

	}

	void Hero::render(float deltaTime)
	{
		heroAnimate(deltaTime);
		updateMovement();

		frameRect.width = width * leftRight;

		
		//Texture2D &texture = getTexture("hero");
	//	Rectangle source{texture.width/8.f * frame,0.f, texture.width/8.f, texture.height/1.f};
		Rectangle dest{GetScreenWidth()/4.f, GetRenderHeight()/2.f,width * 3.f ,height *3.f };
		DrawTexturePro(*texture,frameRect,dest,Vector2{},0.f,WHITE);

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


	void Hero::updateMovement()
	{
		int dirx{0};
		int diry{0};
		int speed{0};

		if (IsKeyDown(KEY_A))
		{
			dirx -= 1.0;
			leftRight = -1.f;

		}
		

		if (IsKeyDown(KEY_D)) 
		{
			dirx += 1.0;
			leftRight = 1.f;
		}

		if (IsKeyDown(KEY_LEFT_SHIFT)) speed += 60.0f;

		std::string resultD = "Direction X output: ";
		resultD += std::to_string(dirx);
//		DrawText(resultD.c_str(),0.f,0.f,40,RED);

		std::map<HeroState, std::string> heroStates = {
			
			{HeroState::idle, "idle"},
			{HeroState::walk, "running"},
			{HeroState::jumping, "jumping"},
			

		};

		std::string outState = "current state: ";

		outState += heroStates[state];



//		outState.append(std::to_string())

//		DrawText(outState.c_str(),0.f,20.f,40,RED);



		switch(state)
		{
			case HeroState::idle:
				if(dirx) state = HeroState::walk;
				if(speed) state = HeroState::running;
				break;

			case HeroState::walk:
			   if(!dirx) state = HeroState::idle;
			   break;
			case HeroState::jumping:
			   if(diry) state = HeroState::jumping;
			   break;
			case HeroState::running:
			   if(!speed) state = HeroState::idle;
			   

		}

		if(state == HeroState::idle)
		{
			texture = &getTexture("hero");
			maxFrames = 14;
		} else if (state == HeroState::walk)
		{
			texture = &getTexture("walk");
			maxFrames = 10;
		} else if (state == HeroState::running){
			texture = &getTexture("run");
			maxFrames = 10;

		}
		



	}



}
