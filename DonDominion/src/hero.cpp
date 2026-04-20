#include "hero.hpp"
#include <iostream>
#include <map>
#include <algorithm>



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
		bulletSpeed = 500.f;
		
	}

	Hero::~Hero(){

	}
	void Hero::updatePlayer(Map& map){
		float deltaTime = GetFrameTime();
		makeAnimation(deltaTime);
		updateBullets(deltaTime);
		updateMovement(deltaTime);
		onGround = false;

		applyGravity();
		pos.y += vel.y;
		resolveCollision(map);
		
	}

	void Hero::updateMovement(float deltaTime){
		int dirx{0};
		int diry{0};
		int speed{0};
		bool shot{false};

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
		if (IsKeyDown(KEY_J)){
			state = HeroState::shot;
			shot = true;


			Bullet newBullet;
			const float left{4};
            const float right{24};
			const float t = (width + 1)/4.0f;
			const float offset = left + right * t;
			std::cout << "offset" << offset << '\n';
			newBullet.pos = {pos.x + (width / 2.f) + 50.f, pos.y + (height-17.f )};
			newBullet.vel = {bulletSpeed * leftRight , 0};
			newBullet.active = true;
			bullets.push_back(newBullet);



		}

		if (IsKeyDown(KEY_LEFT_SHIFT)) speed += 60.0f;

		std::string resultD = "Direction X output: ";
		resultD += std::to_string(dirx);
//		DrawText(resultD.c_str(),0.f,0.f,40,RED);

		std::map<HeroState, std::string> heroStates = {

			{HeroState::idle, "idle"},
			{HeroState::walk, "running"},
			{HeroState::jumping, "jumping"},
			{HeroState::shot, "shot"}


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
				if(shot) state = HeroState::shot;
				break;

			case HeroState::walk:
			   if(!dirx) state = HeroState::idle;
			   break;
			case HeroState::jumping:
			   if(diry) state = HeroState::jumping;
			   break;
			case HeroState::running:
			   if(!speed) state = HeroState::idle;
			case HeroState::shot:
			   if(!shot) state = HeroState::idle;
			


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

		}else if(state == HeroState::shot){
			texture = &getTexture("shot");
			maxFrames = 3;
		}




	}
	void Hero::makeAnimation(float deltaTime){
		runningTime += deltaTime;
		if (runningTime > updateTime){
			++frame;
			runningTime = 0.f;
			if(frame > maxFrames) frame = 0;
			frameRect.x = (float) width * frame;

		}

	}

	void  Hero::render(){

		frameRect.width = width * leftRight;
		Rectangle dest{pos.x, pos.y,width*1.5f, height*1.5f};
		DrawTexturePro(*texture,frameRect,dest,Vector2{},0.f,WHITE);
		DrawRectangleLinesEx(dest,2.f,RED);
//
//
		for(const auto& b : bullets){
			if(b.active){
				Texture2D *bullet = &getTexture("bullet");
				Rectangle bulletSrc{0,0,bullet->width/4.f,bullet->height/1.f};
				Rectangle bulletDest{b.pos.x, b.pos.y, bullet->width/1.f, bullet->height/1.f};
				DrawTexturePro(*bullet,bulletSrc,bulletDest,Vector2{},0,WHITE);
//				DrawCircleV(b.pos, 5.f, YELLOW);
			}
		}


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

	

	void Hero::updateBullets(float deltaTime) {
		for(int i = 0; i < bullets.size(); i++){
			if(bullets[i].active){
				bullets[i].pos.x += bullets[i].vel.x * deltaTime;
//				std::cout << bullets[i].pos.x << "\n";

			}
		}

		bullets.erase(std::remove_if(bullets.begin(), bullets.end(), [](const Bullet& b) {
						return !b.active;
						}), bullets.end());

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
