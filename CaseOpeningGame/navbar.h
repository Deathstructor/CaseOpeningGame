#pragma once

#include "common.h";

constexpr int navbarItemCount = 5;
constexpr int navbarItemWidth = screenWidth / navbarItemCount;
constexpr int navbarItemHeight = 50;
extern int selectedNavbarItem;

struct NavbarItem {
    const char* name;
    const char* id;
};

extern NavbarItem navbarItems[navbarItemCount];

void drawNavbar();