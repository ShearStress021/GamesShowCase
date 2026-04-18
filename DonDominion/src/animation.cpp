#include "animation.hpp"


namespace dominion {
	void Animation::render(const Vector2& pos, const Vector2& size) {
	   DrawTexturePro(*tex, {fwidth, fheight, (flipX ? -fwidth : fwidth), 
			   (flipY ? -fheight : fheight)}, {pos.x, pos.y, size.x, size.y}, {0, 0}, 0, WHITE);
	}
}




