#pragma once
#include "raylib.h"


namespace dominion
{
	void drawText(const Vector2& position, const char* text, float fontSize, float rotation = 0.f);
	void drawTexture(const Texture& texture, const Vector2& position, const Vector2& size, float rotation = 0.f);
	//void drawTexture(const Texture& texture, const Vector2& position, const Vector2& size, float rotation = 0.f, const Color& color = WHITE);
	void drawTextureBlock(const Texture& texture, const Rectangle& rect, const Color& color = WHITE);
	void drawRect(const Color& color);
	Vector2 getScreenCenter();
	Vector2 getOrigin(const Vector2& size);
	Rectangle getBox(const Texture& texture);
	Rectangle getCameraBounds(const Camera2D& camera);
}


