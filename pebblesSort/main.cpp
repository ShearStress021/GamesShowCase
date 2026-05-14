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


struct Container {
	public:
		Container (){

			for(size_t i{}; i < PEBBLE_NUM; i++){
				Pebble pebble{};
				pebble.position = Vector2{random_range(points[0].x + 2, points[3].x - 2), random_range(points[0].y+2, points[1].y-2)};
				pebbles.push_back(pebble);
			}

		}
		void draw(){
			drawPebble();

			DrawSplineLinear(points,4,thickness,RED);
			DrawCircleV(points[0], radius, RED); // Left rim
			DrawCircleV(points[3], radius, RED);


		}

		void drawPebble(){

			for(const auto& pebble: pebbles){
				DrawCircle(pebble.position.x, pebble.position.y,5.f,PURPLE);
			}

		}


		void update(float deltaTime){
			Vector2 mousePoint{GetMousePosition()};

			float targetRotation{};
			float rotation{};

			Vector2 pivot{325.f, 350.f};
			Vector2 displayPoints[4]{};
			size_t i{};
			for(const auto& point: points){
				displayPoints[i] = point;
				i++;
			}


			if(CheckCollisionPointRec(mousePoint, glassHitBox)){
				if(IsMouseButtonPressed(MOUSE_RIGHT_BUTTON)){
					targetRotation+=35.f;
				}
			}

			rotation = Lerp(rotation, targetRotation, 8.f * deltaTime);


			if(rotation != 0) {
				for(size_t i{}; i < 4; i++){
					Vector2 translated = Vector2Subtract(displayPoints[i], pivot);

					Vector2 rotated = Vector2Rotate(translated, -rotation * DEG2RAD);

					points[i] = Vector2Add(rotated, pivot);

					std::cout << points[i].x  << "  " << points[i].y << '\n';
				}
			}

			std::vector<Vector2> getGlassPosition() const{
				Vector2 staticPoints[4] = {
					{300.f, 300.f},
					{300.f, 400.f},
					{350.f, 400.f},
					{350.f, 300.f}
				};

				for (auto& pnt: staticPoints){
					points.push_back(pnt);
				}


				return points;
			}
			



		}

	private:
		Vector2 position{};
		std::vector<Vector2> points{};
//		Vector2 points[4] = {
//			{300.f, 300.f},
//			{300.f, 400.f},
//			{350.f, 400.f},
//			{350.f, 300.f}
//		};

		float thickness = 2.0f;
		float radius = thickness / 2.0f;
		Rectangle glassHitBox{300.f, 300.f, 50.f,100.f};
		std::vector<Pebble> pebbles{};
		Pebble p{};



};

int main(void)
{
    InitWindow(920, 720, "raylib example - basic window");


	Rectangle aglass{300.f, 150.f, 40.f,70.f};
	Rectangle bglass{400.f, 300.f, 40.f,70.f};



	Container glass{};




	SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        BeginDrawing();
            ClearBackground(BLACK);
			glass.draw();
//			glass.update(GetFrameTime());
			DrawCircle(60.f,60.f,20.f,RED);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
