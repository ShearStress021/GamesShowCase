#pragma once
#include <cstdlib>


namespace dominion {
	inline int random(int min, int max) {
	   return min + (rand() % (max - min + 1));
	}

	inline float random(float min, float max) {
	   return min + (float)rand() / (float)RAND_MAX / (max - min);
	}

}
