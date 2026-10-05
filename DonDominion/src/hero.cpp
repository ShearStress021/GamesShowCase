#include "hero.hpp"


namespace dominion {

	Player::Player(const Texture2D& texture) : tex(texture){

	}

	void Player::render() const{
		const float w = tex.width, h = tex.height;
		DrawTexturePro(tex,{0,0,w,h},{200,200,w,h},{},{},WHITE);
	}



}



