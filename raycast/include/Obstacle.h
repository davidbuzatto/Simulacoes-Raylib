#pragma once 
#include "raygui.h"

typedef struct Obstacle {
    Vector2 start;
    Vector2 end;
    Color color;
} Obstacle;

void drawObstacle( Obstacle *ob );