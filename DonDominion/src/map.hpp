#pragma once



#include <string>
#include <vector>
#include "raylib.h"
#include <memory>
#include "resourceManager.hpp"



namespace dominion {

	constexpr int TILE_SIZE = 32;
    constexpr int MAP_COLS  = 80;
    constexpr int MAP_ROWS  = 16;


	enum class BlockType :  unsigned char {
		air=0, grass, panel, brick,ground,dirt
	};


	struct Block {
		BlockType type = BlockType::air;
		Texture* tex = nullptr;

	};


	class Map{
		public:
			Map();
			~Map()=default;
		   void render();
		   int worldWidth() const {return MAP_COLS * TILE_SIZE;}
		   int worldHeight() const {return MAP_ROWS * TILE_SIZE;}
		   void generate();
		   bool isSolid(int col, int row) const ;
		   bool isSolidAtWorld(float worldX, float worldY) const;
		   Rectangle getTileRect(int col, int row) const;

		private:
			std::vector<std::vector<Block>> blocks;

			void setBlock(int x, int y, BlockType type);
			void drawTile(int col, int row) const;





		   // Render map


	};

}
