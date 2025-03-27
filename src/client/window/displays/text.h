#ifndef TEXT
#define TEXT

#include "raylib.h"


void setDefaultFont();
void setFont(Font f);
void drawText(const char* text, int posX, int posY, float fontSize, Color rgba);
void drawTextFont(const char *text, int posX, int posY, float fontSize, Color rgba, Font* font);


#endif
