#pragma once
#include "Obstacle.h"
#include "raylib.h"

typedef struct LightBeam {
    Vector2 start;
    Vector2 end;
    Vector2 endDraw;
    float angle;
    float magnitude;
    Color color;
} LightBeam;

void updateLightBeam( LightBeam *lb, Vector2 *start );
void drawLightBeam( LightBeam *lb );