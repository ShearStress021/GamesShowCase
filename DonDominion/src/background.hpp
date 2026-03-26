
#pragma once

#include "raylib.h"
#include "helper.hpp"


namespace dominion {
	void drawBackGround(const Texture &foreGround, const Texture &backGround, 
			float foreGroundSpeed, float backGroundSpeed, float daySpeed);

	Color fadeColor(const Color &a, const Color &b, float t);

}
