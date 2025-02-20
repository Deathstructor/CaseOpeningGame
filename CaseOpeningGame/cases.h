#pragma once

#include "common.h";

constexpr int casesCount = 41;

struct CaseItem {
	const char* name;
	const char* imagePath;
	float price;
	Texture2D image;
};

extern CaseItem cases[casesCount];

void loadCaseImages();
void unloadCaseImages();
void drawCases();

void DrawTextBoxed(const char* text, Rectangle rec, float fontSize, float spacing, bool wordWrap, Color tint);
void DrawTextBoxedSelectable(Font font, const char* text, Rectangle rec, float fontSize, float spacing, bool wordWrap, Color tint, int selectStart, int selectLength, Color selectTint, Color selectBackTint);