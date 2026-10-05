#pragma once

#include "raylib.h"


namespace dominion {

	Rectangle getBox(const Texture& texture);
	Rectangle getCameraBound(const Camera2D& camera);
	Vector2 getScreenCenter();
	Vector2 getScreenSize();
	Vector2 getOrigin(const Vector2& size);

	void drawTextureBlock(const Texture& texture, const Rectangle& rect, const Color& color = WHITE) ;
	void drawTexture(const Texture& texture, const Vector2& position, const Vector2& size, float rotation = 0.f, const Color& color = WHITE);
	void drawTextureNoOrigin(const Texture &texture, const Vector2 &position, const Vector2 &size, const Color &color);


	// Math
	Vector2 lerp(const Vector2& a, const Vector2& b, float t);

}

