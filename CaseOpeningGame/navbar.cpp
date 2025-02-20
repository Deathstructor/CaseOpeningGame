#include "navbar.h"

NavbarItem navbarItems[navbarItemCount] = {
    { "Cases", "cases" },
    { "Inventory", "inventory" },
    { "Settings", "settings" },
    { "Exit", "exit" }
};

int selectedNavbarItem = 0;

void drawNavbar() {
	Color balanceBoxColor = { 140, 0, 0, 255 };

    for (int i = 0; i < navbarItemCount; i++) {
		Color itemColor = GRAY;

		if (i == selectedNavbarItem) {
			itemColor = BLUE;
		}

		if (CheckCollisionPointRec(GetMousePosition(), { (float)i * navbarItemWidth, 0, navbarItemWidth, navbarItemHeight }) && selectedNavbarItem != i && i != navbarItemCount - 1) {
			itemColor = { 100, 100, 100, 255 };

			if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
				selectedNavbarItem = i;
			}
		}

		if (i < navbarItemCount - 1) {
			DrawRectangle(i * navbarItemWidth, 0, navbarItemWidth, navbarItemHeight, itemColor);
			DrawText(navbarItems[i].name, i * navbarItemWidth + 10, 10, 20, WHITE);
		}
		else {
			DrawRectangle(i * navbarItemWidth, 0, navbarItemWidth, navbarItemHeight, balanceBoxColor);
			DrawText(TextFormat("$%02.02f", balance), i * navbarItemWidth + 10, 10, 20, WHITE);
		}
    }
}