// pebbleSort.cpp : Defines the entry point for the application.
//

#include "pebbleSort.h"
#include <raylib.h>
#include <vector>



Container::Container() {
	for (int i{}; i < 5; i++) {
		Glass glass{};
		glass.points = {
			220.f + (i * 80.f), 300.f
		};




		Rectangle rec{
			glass.points.x,
			glass.points.y,
			50.f,
			110.f
		};

		glassesRec.push_back(rec);
		glasses.push_back(glass);
	}

}

void Container::draw() {
	for (size_t i{}; i < glassesRec.size(); i++) {
		//			DrawSplineLinear(glass.points.data(), glass.points.size(), glass.thickness, RED);
		//			DrawCircleV(glass.points[0], glass.radius, RED);
		//			DrawCircleV(glass.points[3], glass.radius, RED);


				//	DrawRectangleRounded(rec, 0.3f, 8, Color { 180, 200, 240, 60 });
		auto& rec = glassesRec[i];
		auto& glass = glasses[i];
		rlPushMatrix();
		Vector2 pivot{ rec.x + rec.width / 2, rec.y + rec.height / 2 };
		rlTranslatef(pivot.x, pivot.y, 0);
		rlRotatef(glass.currentRotation, 0, 0, 1);
		rlTranslatef(-pivot.x, -pivot.y, 0);

		DrawRectangleRoundedLines(rec, 0.3f, 8, Color{ 180,200,240,240 });
		DrawRectangle(rec.x, rec.y - 2, rec.width - 2, 8, BLACK);
		rlPopMatrix();
		//			DrawLineEx(glass.points[0], glass.points[1], glass.thickness, RED);
		//			DrawLineEx(glass.points[1], glass.points[2], glass.thickness, RED);
		//			DrawLineEx(glass.points[2], glass.points[3], glass.thickness, RED);

	}


}

void Container::update(float deltaTime) {
	Vector2 mouseHitPoint{ GetMousePosition() };

	for (size_t i{}; i < glasses.size(); i++) {
		auto& glass = glasses[i];
		auto& glassRec = glassesRec[i];

		if (CheckCollisionPointRec(mouseHitPoint, glassRec)) {
			if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON)) {

				if (glass.isPoured) {
					glass.targetOffsetX = 0.f;
					glass.targetOffsetY = 0.f;
					glass.targetRotation = 0.f;
					glass.isPoured = false;
				}

				else if (selectedIdx == -1) {
					selectedIdx = (int)i;
					glass.targetOffsetY = -50.f;

				}
				else if (selectedIdx == (int)i) {
					glass.targetOffsetY = 0.f;
					glass.targetRotation = 0.f;
					selectedIdx = -1;

				}
				else {

					auto& sel = glasses[selectedIdx];
					auto& selected = glassesRec[selectedIdx];



					float targetCenterX = glassRec.x + 50.f;
					float selCenterX = selected.x + 50.f;

					sel.targetOffsetX = targetCenterX - selCenterX;
					sel.targetOffsetY = glassRec.y - selected.y - 70.f;

					sel.targetRotation = -70.f;

					sel.isPoured = true;
					selectedIdx = -1;



				}


			}


			float prevY = glass.currentOffsetY;
			float prevX = glass.currentOffsetX;

			glass.currentOffsetY += (glass.targetOffsetY - glass.currentOffsetY) * 8.f * deltaTime;
			glass.currentOffsetX += (glass.targetOffsetX - glass.currentOffsetX) * 8.f * deltaTime;

			float deltaY = glass.currentOffsetY - prevY;
			float deltaX = glass.currentOffsetX - prevX;

			glassRec.y += deltaY;
			glassRec.y += deltaX;


			glass.currentRotation += (glass.targetRotation - glass.currentRotation);

		}






	}

}

