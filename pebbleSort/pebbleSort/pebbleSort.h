// pebbleSort.h : Include file for standard system include files,
// or project specific include files.

#pragma once

#include <iostream>
#include <raylib.h>
#include <vector>
#include <raymath.h>
#include <rlgl.h>

// TODO: Reference additional headers your program requires here.

struct Pebble {
	Vector2 position{};
	Vector2 direction{};
	Color color{};

};

struct Glass {
	Vector2 points{};
	float radius{ 1.f };
	float thickness{ 2.f };
	float targetOffsetX{};
	float currentOffsetX{};
	float targetOffsetY{};
	float currentOffsetY{};

	float currentRotation{};
	float targetRotation{};
	bool isPoured{ false };


};

class Container {

public:
	Container();
	void draw();
	void update(float deltaTime);

private:
	std::vector<Glass> glasses{};
	std::vector<Rectangle> glassesRec{};
	float rotation{};
	int selectedIdx{ -1 };
};
// pebbleSort.h : Include file for standard system include files,
// or project specific include files.

#pragma once

#include <iostream>

// TODO: Reference additional headers your program requires here.
