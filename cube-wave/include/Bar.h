#pragma once
#include "raylib.h"

typedef struct Bar {
    int x;
    int y;
    int width;
    int minHeight;
    int maxHeight;
    int topDiagonalHeight;
    float percent;
    float angle;
    float angleStep;
    Color color;
} Bar;

void updateBar( Bar *bar );
void drawBar( Bar *bar );