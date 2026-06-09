// pebbleSort.cpp : Defines the entry point for the application.
//

#include "pebbleSort.h"
#include <vector>


Container::Container() {
	for (int i{}; i < 5; i++) {
		Glass glass{};
		glass.bound = {
			220.f + (i * 80.f), 300.f,
			50.f,
			110.f
		};
	//	glassesRec.push_back(rec);
		glasses.push_back(glass);
	}

	glasses[0].pebbles = {
		Pebble{PebbleColor::red},
		Pebble{PebbleColor::blue},
	};


}



void Container::draw() {
	for (auto &glass : glasses) {


		auto& rec = glass.bound;
		rlPushMatrix();
		Vector2 pivot{ rec.x + rec.width / 2, rec.y + rec.height / 2 };
		rlTranslatef(pivot.x, pivot.y, 0);
		rlRotatef(glass.currentRotation, 0, 0, 1);
		rlTranslatef(-pivot.x, -pivot.y, 0);

		DrawRectangleRoundedLines(rec, 0.3f, 8, Color{ 180,200,240,240 });
		DrawRectangle(rec.x, rec.y - 2, rec.width - 2, 8, BLACK);

		float pebbleRadius{ 8.f };
		float gap{ 3.f };
		float startY = rec.y + rec.height - pebbleRadius - gap;



		for (size_t j{}; j < glass.pebbles.size(); j++) {
			glass.pebbles[j].center  = {
				rec.x + rec.width / 2,
				startY - j * (pebbleRadius * 2 + gap)

			};
	


			DrawCircleV(glass.pebbles[j].center, pebbleRadius, MapPebbleColor(glass.pebbles[j].color));
		}
		rlPopMatrix();
	}


}

void Container::update(float deltaTime) {
	Vector2 mouseHitPoint{ GetMousePosition() };

	int i{};
	for (auto &glass: glasses) {
		auto& glassRec = glass.bound;

		if (CheckCollisionPointRec(mouseHitPoint, glassRec)) {
			if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {

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
					auto& selected = sel.bound;

					float sourceBottom = selected.y + selected.height;
					float targetTop = glassRec.y;

					float targetCenterX = glassRec.x + glassRec.width / 2 ;
					float selCenterX = selected.x + selected.width / 2;


					bool pourRight = targetCenterX > selCenterX;
					float distance = targetCenterX - selCenterX;
					float direction = (distance > 0 ? -70.f : 70.f)  ;

					sel.targetOffsetX = distance + direction;
					sel.targetOffsetY = targetTop - sourceBottom - 10.f;


					sel.targetRotation = pourRight ? 80.f : -80.f;

					sel.isPoured = true;
					selectedIdx = -1;

					for(auto &peb: sel.pebbles){
						std::cout << " peb move a " << peb.center.x << '\n';
						peb.center.x += 5.f;
						std::cout << " peb move b " << peb.center.x << '\n';
					}



				}


			}



		}
			float prevY = glass.currentOffsetY;
			float prevX = glass.currentOffsetX;

			

			glass.currentOffsetY += (glass.targetOffsetY - glass.currentOffsetY) * 8.f * deltaTime;
			glass.currentOffsetX += (glass.targetOffsetX - glass.currentOffsetX) * 8.f * deltaTime;

			float deltaY = glass.currentOffsetY - prevY;
			float deltaX = glass.currentOffsetX - prevX;

			glassRec.x += deltaX;
			glassRec.y += deltaY;
			glass.currentRotation += (glass.targetRotation - glass.currentRotation)  * 8.f * deltaTime;


			i++;
	}

}

