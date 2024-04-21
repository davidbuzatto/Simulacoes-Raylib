#pragma once
#include "LightBeam.h"

typedef struct LightSource {
    Vector2 pos;
    LightBeam *lightBeams;
    int lightBeamQuantity;
    Color color;
    Vector2 *collidedPoints;
} LightSource;

LightSource *createLightSource( int lightBeamQuantity, Color color, float startAngle, int obstacleCount );
void destroyLightSource( LightSource *ls );
void updateLightSource( LightSource *ls );
void drawLightSource( LightSource *ls );