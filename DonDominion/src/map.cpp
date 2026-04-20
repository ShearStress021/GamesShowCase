#include "map.hpp"
#include <unordered_map>
#include <array>
#include "resourceManager.hpp"
#include "utils.hpp"
#include "background.hpp"
#include <iostream>




namespace dominion {

	static const char* blockTexture(BlockType type){
		switch(type){
			case BlockType::grass: return "grass";
			case BlockType::dirt: return "dirt";
			case BlockType::brick: return "brick";
			case BlockType::panel: return "panel";
			case BlockType::ground: return "ground";
			case BlockType::floor: return "floor";
			default:              return nullptr;


		}
	}


	Map::Map(){
		blocks.assign(MAP_ROWS, std::vector<Block>(MAP_COLS, Block{}));
		generate();
	}


	void Map::setBlock(int col, int row, BlockType type){
		if (col < 0 || col >= MAP_COLS) return;
        if (row < 0 || row >= MAP_ROWS) return;

        auto& b  = blocks[row][col];
        b.type   = type;

        const char* name = blockTexture(type);
        b.tex = (name != nullptr) ? &getTexture(name) : nullptr;
	}

	void Map::generate(){
		// ground level row (0 = top, MAP_ROWS-1 = bottom)
        const int groundLevel = 14; 

        for (int col = 0; col < MAP_COLS; col++) {
			for(int row = 0; row < MAP_ROWS; row++){
				if (row < groundLevel) {
					setBlock(col, row, BlockType::air);
				} else if (row == groundLevel) {
					setBlock(col, row, BlockType::floor); // The surface
				} else {
					setBlock(col, row, BlockType::dirt);  // Fill everything below
				}

			}

        }
	}

	bool Map::isSolid(int col, int row) const {
		if (col < 0 || col >= MAP_COLS || row < 0 || row >= MAP_ROWS) return true; // Bounds check
		return blocks[row][col].type != BlockType::air;


	}

	bool Map::isSolidAtWorld(float worldX, float worldY) const {

		float screenH = (float)GetScreenHeight();

//		float mapTopY = screenH - (MAP_ROWS * TILE_SIZE);
		int col = (int)(worldX / TILE_SIZE);
		int row = (int)((worldY )/ TILE_SIZE);
		return isSolid(col, row);
	}

	Rectangle Map::getTileRect(int col, int row) const {
		return { col * TILE_SIZE * 1.f, row * TILE_SIZE * 1.f,
				 TILE_SIZE * 1.f,       TILE_SIZE * 1.f };
	}

	void Map::drawTile(int col, int row) const {

		const auto& b = blocks[row][col];
        if (b.type == BlockType::air || b.tex == nullptr) return;

//        float height = GetScreenHeight();

        float x = col * TILE_SIZE;
        float y =   row * TILE_SIZE;

        Rectangle src  { 0.f, 0.f, (float)b.tex->width, (float)b.tex->height };
        Rectangle dest { x,   y,   (float)TILE_SIZE,     (float)TILE_SIZE     };

        DrawTexturePro(*b.tex, src, dest, Vector2{}, 0.f, WHITE);

	}

	void Map::render() {
		  for (int row = 0; row < MAP_ROWS; row++)
            for (int col = 0; col < MAP_COLS; col++)
                drawTile(col, row);
	}
}

