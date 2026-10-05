#include <raylib.h>
#include "scenes.hpp"


constexpr int minWindowWidth  = 920;
constexpr int minWindowHeight = 720;

int main(){
	InitWindow(minWindowWidth, minWindowHeight, "Don minion");
	SetExitKey(KEY_NULL);
	SetTargetFPS(60);

	dominion::TextureHandler tex{};
	dominion::Scene scene{};
	dominion::switchScenes(scene, dominion::SceneId::Load, tex);

	while(!WindowShouldClose()) {

		const auto next  = dominion::updateScene(scene, GetFrameTime());



		BeginDrawing();
		ClearBackground(BLACK);
			renderScene(scene);

		EndDrawing();

		if(next){
			if (*next == dominion::SceneId::Quit) break;
			dominion::switchScenes(scene, *next, tex);
			
		}

	}
	CloseWindow();



}
