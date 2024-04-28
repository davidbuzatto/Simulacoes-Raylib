#pragma once

#include "raygui.h"
#include "Bar.h"

typedef struct BarStrip {
    int x;
    int y;
    Bar *bars;
    int barQuantity;
    int barWidth;
    int barMinHeight;
    int barMaxHeight;
    int barTopDiagonalHeight;
    float angleStep;
    Color color;
} BarStrip;

void createBarStrip( 
    BarStrip *newBarStrip,
    int x, int y, int barQuantity, 
    int barWidth, int barMinHeight, int barMaxHeight, int barTopDiagonalHeight,
    float angleStep, Color color, int te );

void destroyBarStrip( BarStrip *bs );
void destroyBarsFromBarStrip( BarStrip *bs );

void updateBarStrip( BarStrip *bs );
void drawBarStrip( BarStrip *bs );