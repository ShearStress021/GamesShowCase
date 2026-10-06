#include "hero.hpp"


namespace dominion {

	Player::Player(const Texture2D& texture) : tex(texture){
		maxFrame = 7;
		width = (float)tex.width  / maxFrame;
		height = tex.height;
		frameRect = {0.f,0.f,(float)width,(float)height};


	}

	void Player::render() const{
		Rectangle dest {200, 200, width * 1.5f, height * 1.5f};
		DrawTexturePro(tex,frameRect,dest,{},{},WHITE);
	}

	void Player::update(float dt){
		makeAnimation(dt);

	}

	void Player::makeAnimation(float dt){
		runningTime += dt;
		if(runningTime > updateTime){
			++ frame;
			runningTime = 0.f;
			if(frame > maxFrame) frame = 0;
			frameRect.x = (float) width * frame;
		}

	}


}



