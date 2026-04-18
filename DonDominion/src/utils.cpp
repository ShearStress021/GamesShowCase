#include "utils.hpp"
#include "raymath.h"



namespace dominion {


	Rectangle getCameraBound(const Camera2D& camera){
		Vector2 pos = GetScreenToWorld2D({0,0},camera);

		return {
			pos.x,pos.y,GetScreenWidth()/camera.zoom, GetScreenHeight()/camera.zoom
		};
	}
	Vector2 getScreenSize() {
		return {
			static_cast<float>(GetScreenWidth()),
			static_cast<float>(GetScreenHeight())
		};
	}


	Rectangle getBox(const Texture& texture) {
	   return {0.f, 0.f, (float)texture.width, (float)texture.height};
	}
	Vector2 getOrigin(const Vector2& size) {

   		return Vector2Scale(size, 0.5f) ;
	}

	Vector2 getScreenCenter()
	{
		return {
			GetScreenWidth() / 2.f,
			GetScreenHeight()/ 2.f
		};
	}


	void drawTextureBlock(const Texture& texture, const Rectangle& rect, const Color& color) {
	   Rectangle src {0, 0, texture.width * (rect.width / rect.height), (float)texture.height};
	   DrawTexturePro(texture, src, rect, {0.f, 0.f}, 0.f, color);
	}

	void drawTexture(const Texture& texture, const Vector2& position, const Vector2& size, float rotation, const Color& color) {
	   DrawTexturePro(texture, getBox(texture), {position.x, position.y, size.x, size.y}, getOrigin(size), rotation, color);
	}
	void drawTextureNoOrigin(const Texture &texture, const Vector2 &position, const Vector2 &size, const Color &color) {
	   DrawTexturePro(texture, getBox(texture), {position.x, position.y, size.x, size.y}, {0, 0}, 0, color);
	}


	// Maths
	Vector2 lerp(const Vector2& a, const Vector2& b, float t) {
	   t = (t < 0.f ? 0.f : (t > 1.f ? 1.f : t));
	   return {a.x + (b.x - a.x) * t, a.y + (b.y - a.y) * t};
	}

}
