// Header files
#include "common.h";
#include "navbar.h";

// Source files
//#include "sidebar.cpp";

using namespace std;

int main() {
	SetTargetFPS(targetFPS);
	InitWindow(screenWidth, screenHeight, "Case Opening Game");

	while (!WindowShouldClose()) {
		BeginDrawing();
		ClearBackground(DARKGRAY);

		drawNavbar();

		EndDrawing();
	}

	return 0;
}