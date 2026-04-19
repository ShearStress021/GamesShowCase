#include "startScene.hpp"

#include "raylib.h"



constexpr int minWindowWidth  = 1080;
constexpr int minWindowHeight = 920;


int main() {
	InitWindow(minWindowWidth, minWindowHeight, "Don minion");
	SetExitKey(KEY_NULL);
	SetTargetFPS(60);


	std::shared_ptr<dominion::Scene> currentScene =  std::make_shared<dominion::StartScene>();

	while(!WindowShouldClose()) {

		if(currentScene->quitScene) {
			auto newScene = currentScene->change();
			currentScene = newScene;
		}

		currentScene->updateStateLogic();

		BeginDrawing();
		 	ClearBackground(WHITE);
			currentScene->render();
		EndDrawing();

	}
	CloseWindow();
}

