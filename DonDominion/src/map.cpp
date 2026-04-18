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
        const int groundRow = MAP_ROWS - 4;

        for (int col = 0; col < MAP_COLS; col++) {

            // --- flat terrain base ---
//            setBlock(col, groundRow ,     BlockType::grass);
            setBlock(col, groundRow + 1, BlockType::dirt);
            setBlock(col, groundRow + 2, BlockType::dirt);
            setBlock(col, groundRow - 1 , BlockType::brick); // bedrock

            // --- raised platforms every 12 columns ---
     //       if (col % 12 == 3) {
       ///         int platformRow = groundRow - 3;
          ///      for (int pc = col; pc < col + 4 && pc < MAP_COLS; pc++) {
             //       setBlock(pc, platformRow, BlockType::panel);
               // }
            //}

            // --- brick pillars every 20 columns ---
           // if (col % 20 == 10) {
             //   setBlock(col, groundRow - 1, BlockType::brick);
               // setBlock(col, groundRow - 2, BlockType::brick);
            //}

            //if (col % 6 == 2){
              //  int brickRow = groundRow - 3;
                //for(int pc = col; pc < col + 3 && pc < MAP_COLS; pc++){
                  //  setBlock(pc, brickRow, BlockType::brick);
                //}
                //setBlock(col, groundRow - 1, BlockType::brick);
            }
        }
	}

	void Map::drawTile(int col, int row) const {

		const auto& b = blocks[row][col];
        if (b.type == BlockType::air || b.tex == nullptr) return;

        float height = GetScreenHeight();

        float x = col * TILE_SIZE;
        float y = height - ((MAP_ROWS - row) * TILE_SIZE);

        Rectangle src  { 0.f, 0.f, (float)b.tex->width, (float)b.tex->height };
        Rectangle dest { x,   y,   (float)TILE_SIZE,     (float)TILE_SIZE     };

        DrawTexturePro(*b.tex, src, dest, Vector2{}, 0.f, WHITE);

	}

	void Map::render() {
		 drawBackGround(backGround, foreGround, 0.001f, 0.002f, 0.2f);
		  for (int row = 0; row < MAP_ROWS; row++)
            for (int col = 0; col < MAP_COLS; col++)
                drawTile(col, row);
	}
}

