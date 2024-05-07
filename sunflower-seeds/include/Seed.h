#pragma once

#include "raylib.h"

typedef struct Seed {
    Vector2 pos;
    float speed;
    float angle;
    float radius;
    float minRadius;
    float maxRadius;
    float maxDistanceToGrow;
    float maxDistanceToChangeColor;
    Color color;
} Seed;

void updateSeed( Seed *seed, float distance );
void drawSeed( Seed *seed );