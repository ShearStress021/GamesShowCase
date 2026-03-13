

#include "game.hpp"

#include <cstdlib>
#include "raylib.h"
#include "gameScene.hpp"
#include <iostream>

namespace dominion {
	Game::Game()
	{
		srand(time(nullptr));
		InitWindow(920, 720, "Don Dominion");
		SetTargetFPS(60);
		SetExitKey(KEY_NULL);
		scenes.push_back(GameScene::make());
		
	}


	Game::~Game()
	{
		CloseWindow();
	}


	void Game::run()
	{
		std::cout << scenes.size() << '\n';
		while(not WindowShouldClose())
		{
			if(scenes.front() -> quitScene)
			{
				scenes.front()->change(scenes);
				scenes.pop_front();
			}

			if(scenes.empty())
			{
				return;
			}
			scenes.front()->update();
			scenes.front()->render();
		}
	}

}
