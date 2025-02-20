// Header files
#include "common.h";
#include "navbar.h";
#include "cases.h";

int main() {
	SetTargetFPS(targetFPS);
	InitWindow(screenWidth, screenHeight, "Case Opening Game");

	loadCaseImages();
	
	bool exit = false;

	while (!WindowShouldClose() && !exit) {
		BeginDrawing();
		ClearBackground(DARKGRAY);

		switch (selectedNavbarItem) {
		case 0:
			// Cases
			drawCases();
			break;
		case 1:
			// Inventory
			break;
		case 2:
			// Settings
			break;
		case 3:
			// Exit
			exit = true;
			break;
		default:
			// Cases
			break;
		}

		drawNavbar();

		EndDrawing();
	}

	unloadCaseImages();

	return 0;
}