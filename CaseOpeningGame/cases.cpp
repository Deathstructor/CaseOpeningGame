#include "cases.h";

CaseItem cases[casesCount] = {
    { "Gallery Case", "assets/gallery.png", 0.71f },
    { "Kilowatt Case", "assets/kilowatt.png", 0.57f },
    { "Revolution Case", "assets/revolution.png", 0.33f },
    { "Recoil Case", "assets/recoil.png", 0.17f },
    { "Dreams & Nightmares Case", "assets/dreams.png", 1.35f },
    { "Operation Riptide Case", "assets/riptide.png", 4.89f },
    { "Snakebite Case", "assets/snakebite.png", 0.23f },
    { "Operation Broken Fang Case", "assets/broken_fang.png", 4.00f },
    { "Fracture Case", "assets/fracture.png", 0.22f },
    { "Prisma 2 Case", "assets/prisma2.png", 0.60f },
    { "CS20 Case", "assets/cs20.png", 0.44f },
    { "Shattered Web Case", "assets/shattered_web.png", 3.28f },
    { "Prisma Case", "assets/prisma.png", 0.56f },
    { "Danger Zone Case", "assets/danger_zone.png", 0.64f },
    { "Horizon Case", "assets/horizon.png", 0.77f },
    { "Clutch Case", "assets/clutch.png", 0.40f },
    { "Spectrum 2 Case", "assets/spectrum2.png", 1.62f },
    { "Operation Hydra Case", "assets/hydra.png", 17.25f },
    { "Spectrum Case", "assets/spectrum.png", 2.65f },
    { "Glove Case", "assets/glove.png", 5.58f },
    { "Gamma 2 Case", "assets/gamma2.png", 2.11f },
    { "Gamma Case", "assets/gamma.png", 2.14f },
    { "Chroma 3 Case", "assets/chroma3.png", 1.98f },
    { "Operation Wildfire Case", "assets/wildfire.png", 1.89f },
    { "Revolver Case", "assets/revolver.png", 1.69f },
    { "Shadow Case", "assets/shadow.png", 0.75f },
    { "Falchion Case", "assets/falchion.png", 0.81f },
    { "Chroma 2 Case", "assets/chroma2.png", 2.21f },
    { "Chroma Case", "assets/chroma.png", 2.57f },
    { "Operation Vanguard Weapon Case", "assets/vanguard.png", 2.43f },
    { "eSports 2014 Summer Case", "assets/esports2014.png", 7.35f },
    { "Operation Breakout Weapon Case", "assets/breakout.png", 5.81f },
    { "Huntsman Weapon Case", "assets/huntsman.png", 9.43f },
    { "Operation Phoenix Weapon Case", "assets/phoenix.png", 3.01f },
    { "CS:GO Weapon Case 3", "assets/weapon_case3.png", 6.71f },
    { "Winter Offensive Weapon Case", "assets/winter_offensive.png", 6.04f },
    { "eSports 2013 Winter Case", "assets/esports2013winter.png", 8.57f },
    { "CS:GO Weapon Case 2", "assets/weapon_case2.png", 11.62f },
    { "Operation Bravo Case", "assets/bravo.png", 44.38f },
    { "eSports 2013 Case", "assets/esports2013.png", 41.07f },
    { "CS:GO Weapon Case", "assets/weapon_case.png", 85.36f }
};

void loadCaseImages() {
	for (int i = 0; i < casesCount; i++) {
		cases[i].image = LoadTexture(cases[i].imagePath);
	}
}

void unloadCaseImages() {
	for (int i = 0; i < casesCount; i++) {
		UnloadTexture(cases[i].image);
	}
}


void DrawTextBoxed(const char* text, Rectangle rec, float fontSize, float spacing, bool wordWrap, Color tint)
{
    DrawTextBoxedSelectable(GetFontDefault(), text, rec, fontSize, spacing, wordWrap, tint, 0, 0, WHITE, WHITE);
}

// Draw text using font inside rectangle limits with support for text selection
static void DrawTextBoxedSelectable(Font font, const char* text, Rectangle rec, float fontSize, float spacing, bool wordWrap, Color tint, int selectStart, int selectLength, Color selectTint, Color selectBackTint)
{
    int length = TextLength(text);  // Total length in bytes of the text, scanned by codepoints in loop

    float textOffsetY = 0;          // Offset between lines (on line break '\n')
    float textOffsetX = 0.0f;       // Offset X to next character to draw

    float scaleFactor = fontSize / (float)font.baseSize;     // Character rectangle scaling factor

    // Word/character wrapping mechanism variables
    enum { MEASURE_STATE = 0, DRAW_STATE = 1 };
    int state = wordWrap ? MEASURE_STATE : DRAW_STATE;

    int startLine = -1;         // Index where to begin drawing (where a line begins)
    int endLine = -1;           // Index where to stop drawing (where a line ends)
    int lastk = -1;             // Holds last value of the character position

    for (int i = 0, k = 0; i < length; i++, k++)
    {
        // Get next codepoint from byte string and glyph index in font
        int codepointByteCount = 0;
        int codepoint = GetCodepoint(&text[i], &codepointByteCount);
        int index = GetGlyphIndex(font, codepoint);

        // NOTE: Normally we exit the decoding sequence as soon as a bad byte is found (and return 0x3f)
        // but we need to draw all of the bad bytes using the '?' symbol moving one byte
        if (codepoint == 0x3f) codepointByteCount = 1;
        i += (codepointByteCount - 1);

        float glyphWidth = 0;
        if (codepoint != '\n')
        {
            glyphWidth = (font.glyphs[index].advanceX == 0) ? font.recs[index].width * scaleFactor : font.glyphs[index].advanceX * scaleFactor;

            if (i + 1 < length) glyphWidth = glyphWidth + spacing;
        }

        // NOTE: When wordWrap is ON we first measure how much of the text we can draw before going outside of the rec container
        // We store this info in startLine and endLine, then we change states, draw the text between those two variables
        // and change states again and again recursively until the end of the text (or until we get outside of the container).
        // When wordWrap is OFF we don't need the measure state so we go to the drawing state immediately
        // and begin drawing on the next line before we can get outside the container.
        if (state == MEASURE_STATE)
        {
            // TODO: There are multiple types of spaces in UNICODE, maybe it's a good idea to add support for more
            // Ref: http://jkorpela.fi/chars/spaces.html
            if ((codepoint == ' ') || (codepoint == '\t') || (codepoint == '\n')) endLine = i;

            if ((textOffsetX + glyphWidth) > rec.width)
            {
                endLine = (endLine < 1) ? i : endLine;
                if (i == endLine) endLine -= codepointByteCount;
                if ((startLine + codepointByteCount) == endLine) endLine = (i - codepointByteCount);

                state = !state;
            }
            else if ((i + 1) == length)
            {
                endLine = i;
                state = !state;
            }
            else if (codepoint == '\n') state = !state;

            if (state == DRAW_STATE)
            {
                textOffsetX = 0;
                i = startLine;
                glyphWidth = 0;

                // Save character position when we switch states
                int tmp = lastk;
                lastk = k - 1;
                k = tmp;
            }
        }
        else
        {
            if (codepoint == '\n')
            {
                if (!wordWrap)
                {
                    textOffsetY += (font.baseSize + font.baseSize / 2) * scaleFactor * 0.7;
                    textOffsetX = 0;
                }
            }
            else
            {
                if (!wordWrap && ((textOffsetX + glyphWidth) > rec.width))
                {
                    textOffsetY += (font.baseSize + font.baseSize / 2) * scaleFactor * 0.7;
                    textOffsetX = 0;
                }

                // When text overflows rectangle height limit, just stop drawing
                if ((textOffsetY + font.baseSize * scaleFactor) > rec.height) break;

                // Draw selection background
                bool isGlyphSelected = false;
                if ((selectStart >= 0) && (k >= selectStart) && (k < (selectStart + selectLength)))
                {
                    Rectangle rect = { rec.x + textOffsetX - 1, rec.y + textOffsetY, glyphWidth, (float)font.baseSize * scaleFactor };
                    DrawRectangleRec(rect, selectBackTint);
                    isGlyphSelected = true;
                }

                // Draw current character glyph
                if ((codepoint != ' ') && (codepoint != '\t'))
                {
                    Vector2 position = { rec.x + textOffsetX, rec.y + textOffsetY };
                    DrawTextCodepoint(font, codepoint, position, fontSize, isGlyphSelected ? selectTint : tint);
                }
            }

            if (wordWrap && (i == endLine))
            {
                textOffsetY += (font.baseSize + font.baseSize / 2) * scaleFactor * 0.7;
                textOffsetX = 0;
                startLine = endLine;
                endLine = -1;
                glyphWidth = 0;
                selectStart += lastk - k;
                k = lastk;

                state = !state;
            }
        }

        if ((textOffsetX != 0) || (codepoint != ' ')) textOffsetX += glyphWidth;  // avoid leading spaces
    }
}

int itemYPosition = 50;

void drawCases() {
    itemYPosition += GetMouseWheelMove() * scrollSpeed;
    if (itemYPosition >= 50) {
		itemYPosition = 50;
	}

    if (itemYPosition <= -(50 + ((casesCount - 1) / 4) * 300) + 650) {
        itemYPosition = -(50 + ((casesCount - 1) / 4) * 300) + 650;
	}

	cout << itemYPosition << endl;

	for (int i = 0; i < casesCount; i++) {
        Vector2 textSize = MeasureTextEx(GetFontDefault(), TextFormat("%02.02f", cases[i].price), 20.0f, 2.0f);
        DrawText(TextFormat("$%02.02f", cases[i].price), (30 + (i % 4) * 300), itemYPosition + (i / 4) * 300 + 230, 20, WHITE);

	    Rectangle caseTextBox = { 30 + (i % 4) * 300, itemYPosition + (i / 4) * 300 + 260, 230, 50 };
		DrawTexture(cases[i].image, 20 + (i % 4) * 300, itemYPosition + (i / 4) * 300, WHITE);
		DrawTextBoxed(cases[i].name, caseTextBox, 20.0f, 2.0f, true, WHITE);
	}
}