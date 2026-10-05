#pragma once
#include "helpers.hpp"


namespace dominion {
	class Player {
		public:
			Player(const Texture2D& texture);
			void render() const;
		private:
			const Texture2D& tex;

	};
	

}




