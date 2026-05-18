#include <iostream>
#include "raylib.h"
#include <random>
#include <vector>
#include <raymath.h>

static int PEBBLE_NUM{30};

struct Pebble {  
	Vector2 position{};
	Color color{};


};

float random_range(float min, float max){
	static std::mt19937 generator {std::random_device()()};
	std::uniform_real_distribution<float> range{min, max};
	return range(generator);
}


struct Glass {
	Glass () {

	}
	std::vector<Vector2> getPointPosition(){
		return points;
	}

	std::vector<Vector2> points{};
	std::vector<Vector2> basePoints{};

	float thickness = 2.0f;
	float radius = thickness / 2.0f;
	float targetOffsetY{};
	float currentOffsetY{};
	float targetRotation{};
	float currentRotation{};
	float targetOffsetX{};
	float currentOffsetX{};
	bool isPoured{false};

};

class Containers {

	public:
		Containers(){
			for(size_t i{}; i < 5 ; i ++){
				Glass glass{};
				glass.basePoints=  {
					{220.f + (i * 80.f), 300.f },
					{220.f + (i * 80.f), 400.f },
					{270.f + (i * 80.f), 400.f },
					{270.f + (i * 80.f), 300.f }


				};
				glass.points =  glass.basePoints;
				Rectangle glassHit{glass.points[0].x, glass.points[0].y,50.f, 100.f };
				glassHitBoxs.push_back(glassHit);
				glasses.push_back(glass);
				

			}
		}


		void draw(){
			for(const auto& glass: glasses){
				DrawSplineLinear(glass.points.data(),glass.points.size(),glass.thickness,RED);
				DrawCircleV(glass.points[0], glass.radius, RED); 
				DrawCircleV(glass.points[3], glass.radius, RED);

			}
		}

		void update(float deltaTime){

			Vector2 mouseHitPoint{GetMousePosition()};

			for(size_t i{}; i < glasses.size(); i++){

				auto& g = glasses[i];
				if(CheckCollisionPointRec(mouseHitPoint, glassHitBoxs[i])){
					if(IsMouseButtonPressed(MOUSE_RIGHT_BUTTON)){

						if(g.isPoured){

							g.targetOffsetX = 0.f;
							g.targetOffsetY = 0.f;
							g.targetRotation = 0.f;
							g.isPoured = false;

						}

						else if(selectedIdx == -1){
							selectedIdx = (int)i;
							g.targetOffsetY = -30.f;

						}
						else if(selectedIdx == (int)i){
							g.targetOffsetY = 0.f;
							g.targetRotation = 0.f;
							selectedIdx = -1;

						}
						else {
							auto& sel = glasses[selectedIdx];

							float targetCenterX = g.basePoints[0].x + 50.f;
							float selCenterX = sel.basePoints[0].x + 50.f;

							sel.targetOffsetX = targetCenterX - selCenterX;
							sel.targetOffsetY = g.basePoints[0].y - sel.basePoints[0].y - 70.f;

							sel.targetRotation = -80.f;
							sel.isPoured = true;
							selectedIdx = -1;

						}
					}
				}

				float prev = g.currentOffsetY;
				float prevRot = g.currentRotation;
				float prevX = g.currentOffsetX;

				g.currentOffsetX +=(g.targetOffsetX - g.currentOffsetX) * 8.f * deltaTime;
				g.currentOffsetY += (g.targetOffsetY - g.currentOffsetY)* 8.f * deltaTime;
				g.currentRotation+= (g.targetRotation - g.currentRotation) * 8.f * deltaTime;


				float delta = g.currentOffsetY - prev;
				float deltaRot = g.currentRotation - prevRot;
				float deltaX = g.currentOffsetX - prevX;
				
				Vector2 pivot {g.basePoints[0].x + 35.f + g.currentOffsetX, g.basePoints[0].y + 23.f + g.currentOffsetY};
		//		for(size_t j{}; j < g.basePoints.size(); j++){
				for(auto& p : g.points){
				//	Vector2 p = g.points[j];
					p.y += delta;
					p.x += deltaX;
					Vector2 translated = Vector2Subtract(p, pivot);
					Vector2 rotate = Vector2Rotate(translated, deltaRot* DEG2RAD);
					p = Vector2Add(rotate, pivot);
			//		glassHitBoxs[i].y = p.x;


				}

				glassHitBoxs[i].y =  pivot.y ;
				glassHitBoxs[i].x = pivot.x - 35.f;
				
//				DrawRectangleLines(glassHitBoxs[i].x, glassHitBoxs[i].y,glassHitBoxs[i].width, glassHitBoxs[i].height,BLUE);


			}

		}
	private:
		std::vector<Glass> glasses{};
		std::vector<Rectangle> glassHitBoxs{};
		int selectedIdx{-1};

};
int main(void)
{
    InitWindow(920, 720, "raylib example - basic window");

	Containers container{};

	SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();
            ClearBackground(BLACK);
			container.draw();
			container.update(GetFrameTime());
//			glass.update(GetFrameTime());
			DrawCircle(60.f,60.f,20.f,RED);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
