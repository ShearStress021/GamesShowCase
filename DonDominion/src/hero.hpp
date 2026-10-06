#pragma once
#include "helpers.hpp"


namespace dominion {
	class Player {
		public:
			Player(const Texture2D& texture);
			void render() const;
			void update(float dt);
		private:
			const Texture2D& tex;
			Rectangle frameRect{};
			float width{};
			float height{};
			int maxFrame{};
			int frame{};

			float runningTime{};
			float updateTime{1/12.f};

		

			void makeAnimation(float dt);

	};
	

}




