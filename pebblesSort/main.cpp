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

};

struct Containers {

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

					g.targetOffsetY = (g.targetOffsetY == 0.0f) ? -50.f : 0.0f;
					g.targetRotation = (g.targetRotation == 0.0f) ? -80.f : 0.0f;
					
				}
			}

			float prev = g.currentOffsetY;
			float prevRot = g.currentRotation;

			g.currentOffsetY += (g.targetOffsetY - g.currentOffsetY)* 8.f * deltaTime;
			g.currentRotation+= (g.targetRotation - g.currentRotation) * 8.f * deltaTime;


			float delta = g.currentOffsetY - prev;
			float deltaRot = g.currentRotation - prevRot;
			
			Vector2 pivot {g.points[0].x + 25, g.points[0].y + 50.f};
	//		for(size_t j{}; j < g.basePoints.size(); j++){
			for(auto& p : g.points){
			//	Vector2 p = g.points[j];
				p.y += delta;
				Vector2 translated = Vector2Subtract(p, pivot);
				Vector2 rotate = Vector2Rotate(translated, deltaRot* DEG2RAD);
				p = Vector2Add(rotate, pivot);


			}

			glassHitBoxs[i].y = g.basePoints[0].y + g.currentOffsetY;


		}

	}

	std::vector<Glass> glasses{};
	std::vector<Rectangle> glassHitBoxs{};




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
