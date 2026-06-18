#pragma once

#include <iostream>
#include <raylib.h>
#include <vector>
#include <raymath.h>
#include <rlgl.h>


enum class PebbleColor {
	red, blue , green, yellow, 
	purple, orange, pink,cyan 
};

inline Color MapPebbleColor(PebbleColor c) {

	switch (c) {

		case PebbleColor::red:    return{ 255, 60, 60, 255 };
		case PebbleColor::blue:   return { 60, 120, 255,255 };
		case PebbleColor::green:  return { 60, 200, 60, 255 };
		case PebbleColor::yellow: return { 255, 220, 40, 255 };
		case PebbleColor::purple: return { 180, 60, 255, 255 };
		case PebbleColor::orange: return { 255, 140, 20, 255 };
		case PebbleColor::pink:   return { 255, 100, 180, 255 };
		case PebbleColor::cyan:   return { 40, 220, 255, 255 };
	}
	return WHITE;

}

struct Pebble {
	PebbleColor color{};
	float targetOffsetX{};
	float currentOffsetX{};
	Vector2 center{};
	Vector2 position{};



};

struct Glass {
	//Vector2 points{};
	Rectangle bound{};
	std::vector<Pebble> pebbles{ };
	float radius{ 1.f };
	float thickness{ 2.f };
	float targetOffsetX{};
	float currentOffsetX{};
	float targetOffsetY{};
	float currentOffsetY{};
	float currentRotation{};
	float targetRotation{};
	bool isPoured{ false };
	int maxPebbles{ 4 };


	void draw(float x, float y){

	}


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
