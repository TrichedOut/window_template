#include "text.h"
#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>


Font* defaultFont;
int loadedDefault = 0;
Font currentFont;

void setFont(Font f) {
  currentFont = f;
}

void setDefaultFont() {
  // if the font hasn't been loaded, load it
  if (!loadedDefault) {
    loadedDefault = 1;

    Font f = LoadFont("assets/font/FiraCodeNerdFontMono-Regular.ttf");

    // malloc and copy fields to default
    defaultFont = malloc(sizeof(Font));
    defaultFont->baseSize = f.baseSize;
    defaultFont->glyphCount = f.glyphCount;
    defaultFont->glyphPadding = f.glyphPadding;
    defaultFont->glyphs = f.glyphs;
    defaultFont->recs = f.recs;
    defaultFont->texture = f.texture;
  }

  setFont(*defaultFont);
}

void drawText(const char* text, int posX, int posY, float fontSize, Color rgba) {
  drawTextFont(text, posX, posY, fontSize, rgba, defaultFont);
}

void drawTextFont(const char *text, int posX, int posY, float fontSize, Color rgba, Font* font) {
  DrawTextEx(*font, text, (Vector2){posX, posY}, fontSize, -1, rgba);
}
