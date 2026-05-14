#include "raylib.h"
#include <random>
#include <vector>

static int PEBBLE_NUM{30};

struct Pebble {  
	Vector2 position{};
	Color color{};

	void draw(){
		DrawCircle(position.x+30, position.y+10,10.f,PURPLE) ;
	}

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
				pebble.position = Vector2{random_range(points[0].x, points[3].x), random_range(points[0].y, points[1].y)};
				pebbles.push_back(pebble);
			}

		}
		void draw(){
			drawPebble();

			update();
			DrawSplineLinear(points,4,thickness,RED);
			DrawCircleV(points[0], radius, RED); // Left rim
			DrawCircleV(points[3], radius, RED);


		}

		void drawPebble(){

			for(const auto& pebble: pebbles){
				DrawCircle(pebble.position.x, pebble.position.y,5.f,PURPLE);
			}

		}


		void update(){
			Vector2 mousePoint{GetMousePosition()};

			if(CheckCollisionPointRec(mousePoint, glassHitBox)){
				if(IsMouseButtonPressed(MOUSE_RIGHT_BUTTON)){
					points[0] = {250, 305};
					points[1] =  {320,405};
					points[2] = {400,350};
					points[3] = {300,305};
					
				}
			}
		}

	private:
		Vector2 position{};
		Vector2 points[4] = {
			{300.f, 300.f},
			{300.f, 400.f},
			{350.f, 400.f},
			{350.f, 300.f}
		};

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
			DrawCircle(60.f,60.f,20.f,RED);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
