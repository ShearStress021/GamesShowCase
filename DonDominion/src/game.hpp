#pragma once

#include "scene.hpp"

namespace dominion {
	class Game {
		Scenes scenes;


		public:
			Game();
			~Game();

			void run();

	};

}

