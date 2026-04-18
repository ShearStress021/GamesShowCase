#pragma once
#include "raylib.h"


namespace dominion {

	struct Animation {
	   Texture* tex;
	   float fwidth = 0;
	   float fheight = 0;
	   float fx = 0;
	   float fy = 0;
	   bool flipX = false;
	   bool flipY = false;

	   void render(const Vector2& pos, const Vector2& size);

	};

}
