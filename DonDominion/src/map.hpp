#pragma once



#include <string>
#include <vector>
#include "raylib.h"
#include <memory>
#include "resourceManager.hpp"



namespace dominion {


	struct Block {
		enum Type {grass, panel, brick,ground,dirt};
		using id_t = unsigned char;


		Texture* tex = nullptr;
		Type type = Type::grass;

		id_t id = 0;
		unsigned char value = 0;
		unsigned char value2 = 0;
		static int getId(const std::string& name);
		



	};


	class Map{
		public:
		   void init();
		   void render(Camera2D& camera);
		   int sizeX = 0;
			int sizeY = 0;

		   bool isPositionValid(int x, int y);
		   bool is(int x, int y, Block::Type type);
		   bool isTransparent(int x, int y);

		   std::vector<Block>& operator[](size_t index);
			void setBlock(int x, int y, const std::string& name);
			void setBlock(int x, int y, Block::id_t id);
			void deleteBlock(int x, int y);
			void moveBlock(int ox, int oy, int nx, int ny);

		private:
			std::vector<std::vector<Block>> blocks;





		   const Texture &backGround{getTexture("back")};
		   const Texture &foreGround{getTexture("ground")};


		   // Render map


	};

}
