#include "objectScene.hpp"
#include "resource.hpp"
#include "helper.hpp"


namespace dominion 
{
	namespace {
		constexpr int SIZE_X{500};
		constexpr int SIZE_Y{500};
	}


	ObjectScene::ObjectScene()
	{
		blocks = std::vector<std::vector<Block>>(SIZE_Y, std::vector<Block>(SIZE_X, Block{}));


		for(int x = 0; x < SIZE_X; ++x)
		{
			for(int y = 0; y < SIZE_Y; ++y)
			{
				if(blocks[y][x].tex)
				{
					continue;
				}

				for(int j = y + 1; j < SIZE_Y; ++j)
				{
					blocks[j][x].tex = &ResourceManager::get().getTexture("grass");
				}
				continue;
			}
		}
	   camera.target = {0.f, 0.f};
	   camera.offset = getScreenCenter();
	   camera.rotation = 0.0f;
	   camera.zoom = 50.f;
	}

	void ObjectScene::update()
	{

	}

	void ObjectScene::render()
	{
		drawRect(BLUE);
		auto crect = getCameraBounds(camera);
		int drew = 0;

		BeginMode2D(camera);
		auto maxY = std::min(SIZE_Y, int((crect.y + crect.height)) + 1);
		auto maxX = std::min(SIZE_X, int((crect.x + crect.width)) + 1);

		for (int y = std::max(0, int(crect.y)); y < maxY; ++y) {
			for (int x = std::max(0, int(crect.x)); x < maxX; ++x) {
				 auto& block = blocks[y][x];
				 if (not block.tex) {
					continue;
				 }
				 drawTextureNO(*block.tex, {(float)x, (float)y, 1.f, 1.f});
				 drew++;
			}
		}
		EndMode2D();

	}

	void ObjectScene::change(Scenes& scenes)
	{

	}

}
