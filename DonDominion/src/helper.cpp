#include "helper.hpp"
#include <csetjmp>


namespace dominion 
{
	Vector2 getScreenCenter()
	{
		return {
			GetScreenWidth() / 2.f,
			GetScreenHeight()/ 2.f
		};
	}
	Vector2 getOrigin(const Vector2& size) {

   		return {size.x / 2.f, size.y / 2.f};
	}

	Rectangle getBox(const Texture& texture) {

	   return {0.f, 0.f, (float)texture.width, (float)texture.height};
	}

	Rectangle getCameraBounds(const Camera2D& camera) {
   	   Vector2 pos = GetScreenToWorld2D({0, 0}, camera);
	   return {pos.x, pos.y, GetScreenWidth() / camera.zoom, GetScreenHeight() / camera.zoom};
	}

	void drawText(const Vector2& position, const char* text, float fontSize)
	{

	}
	void drawTexture(const Texture& texture, const Vector2& position, const Vector2& size, float rotation, const Color& color) {
	   DrawTexturePro(texture, getBox(texture), {position.x, position.y, size.x, size.y}, getOrigin(size), rotation, color);
	}
	void drawTextureBlock(const Texture& texture, const Rectangle& rect, const Color& color) {
	   Rectangle src {0, 0, texture.width * (rect.width / rect.height), (float)texture.height};
	   DrawTexturePro(texture, src, rect, {0.f, 0.f}, 0.f, color);
	}
	void drawRect(const Color& color)
	{
		DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), color);
	}


}
