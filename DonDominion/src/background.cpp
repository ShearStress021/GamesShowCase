#include "background.hpp"

namespace dominion {

	constexpr inline float parallaxBgSpeed = 75.0f;
	constexpr inline float parallaxFgSpeed = 100.0f;

	static float fgProgress = 0;
	static float bgProgress = 0;

	constexpr Color backgroundTintNight = {35, 35, 35, 255};
	constexpr Color backgroundTintDay   = {190, 190, 170, 255};
	constexpr Color foregroundTintNight = {40, 40, 40, 255};
	constexpr Color foregroundTintDay   = {210, 210, 190, 255};

	void drawBackGround(const Texture &background, const Texture &foreGround, float backGroundSpeed, 
			float foreGroundSpeed, float daySpeed)
	{
		Vector2 screenSize = getScreenSize();
		Vector2 origin = getOrigin(screenSize);


		bgProgress -= backGroundSpeed * parallaxBgSpeed;

	   fgProgress -= foreGroundSpeed * parallaxFgSpeed;

	   if (bgProgress <= -screenSize.x) {
		  bgProgress = 0.f;
	   }
	   if (bgProgress > 0.f) {
		  bgProgress = -screenSize.x;
	   }

	   if (fgProgress <= -screenSize.x) {
		  fgProgress = 0.f;
	   }
	   if (fgProgress > 0.f) {
		  fgProgress = -screenSize.x;
   	   }
	   float t = 1.1f;
	      // Draw backgrounds
	   Color bgColor = fadeColor(backgroundTintNight, backgroundTintDay, t);
	   drawTextureNoOrigin(background, {bgProgress, 0}, screenSize, bgColor);
	   drawTextureNoOrigin(background, {screenSize.x + bgProgress, 0}, screenSize, bgColor);

	   Color fgColor = fadeColor(foregroundTintNight, foregroundTintDay, t);
//	   drawTextureNoOrigin(foreGround, {fgProgress, 0}, screenSize, fgColor);
//	   drawTextureNoOrigin(foreGround, {screenSize.x + fgProgress, 0}, screenSize, fgColor);




	}

	Color fadeColor(const Color &a, const Color &b, float t) {
   	   float i = 1.0f - t;
	   return {(unsigned char)((a.r * i) + (b.r * t)), (unsigned char)((a.g * i) + (b.g * t)), 
		   (unsigned char)((a.b * i) + (b.b * t)), 255};
	}


}
