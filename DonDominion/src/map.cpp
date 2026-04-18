#include "map.hpp"
#include <unordered_map>
#include <array>
#include "resourceManager.hpp"
#include "utils.hpp"
#include "background.hpp"




namespace dominion {
	constexpr Block::id_t idCount = 5;	



	static std::unordered_map<std::string, Block::id_t> blockIds {
		{"grass", 0}, {"panel", 1}, {"ground", 2}, {"dirt", 3}, {"brick", 4}
	};



	static std::unordered_map<Block::id_t, std::string> blockNames {
		{0, "grass"}, {1, "panel"}, {2, "ground"}, {3, "dirt"}, {4, "brick"}

	};

	constexpr static std::array<Block::Type, idCount> blockTypes {{
		Block::grass, Block::panel,Block::ground , Block::dirt, Block::brick

	}};


	void Map::init(){
		blocks = std::vector<std::vector<Block>>(sizeY, std::vector<Block>(sizeX, Block{}));
	}


	void Map::setBlock(int x, int y,const std::string& name) 
	{

		auto &block = blocks[y][x];
		block.id = blockIds[name];
		block.value = block.value2 = 0;
		block.type = blockTypes[block.id];

		if (block.id != 0){
			block.tex = &getTexture(name);
		}

	}

	void Map::setBlock(int x, int y, Block::id_t id) {
		auto &block = blocks[y][x];
		block.id = id;
		block.type = blockTypes[block.id];

		if (block.id != 0){
			block.tex = &getTexture(blockNames[id]);
		}


	}

	void Map::deleteBlock(int x, int y) {
		auto& block = blocks[y][x];
		block.tex = nullptr;
		block.type = Block::grass;
		block.id = block.value = block.value2 = 0;

	}


	bool Map::isPositionValid(int x, int y) {
		return x >= 0 and x < sizeX and y >= 0 and y < sizeY;
	}


	bool Map::is(int x, int y, Block::Type type){
		return isPositionValid(x, y) and blocks[y][x].type == type;
	}


	std::vector<Block>& Map::operator[](size_t index) {
		return blocks[index];
	}

	void Map::render(Camera2D& camera){
		drawBackGround(backGround,foreGround,0.001f, 0.002f,0.2f);
		
		auto bounds = getCameraBound(camera);

		auto minX = std::max(0, int(bounds.x));
		auto minY = std::max(0, int(bounds.y));
		auto maxX = std::min(sizeX, int(bounds.x + bounds.width) +1);
		auto maxY = std::min(sizeY, int(bounds.y + bounds.height) +1);

		for(int y = minY; y < maxY; ++y){
			for(int x = minX; x < maxX; ++x ){
				auto& block = blocks[y][x];

				if (block.type == Block::grass)
				{
					continue;
				}

				int ox = x;
				while(x < maxX and blocks[y][x].id == block.id){
					++x;
				}

				if (camera.zoom <= 12.5f){
					DrawRectangle(ox, y,ox-x,1,GREEN);
				}else {
					drawTextureBlock(*block.tex, {(float)ox, (float)y, float(x - ox), 1.f});
				}
			}


		 }
		
	}
}

