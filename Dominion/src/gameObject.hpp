
#pragma once
#include "raymath.h"

namespace dominion {
	enum  class ObjectType {
		bullet, enemy
	};

	enum class BulletState {
		moving, colling, inactive
	};

	struct BulletData {
		BulletState state;

		BulletData(): state(BulletState::moving){

		}

	};

	union ObjectData {
		BulletData bullet;

	};


	struct GameObject {
		ObjectData data{};
		ObjectType type{};

		Vector2 position, velocity, accellation;



	};

}
