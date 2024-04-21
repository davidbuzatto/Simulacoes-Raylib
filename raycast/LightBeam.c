#include <math.h>

#include "LightBeam.h"
#include "raylib.h"
#include "utils.h"

void updateLightBeam( LightBeam *lb, Vector2 *start ) {
    lb->start = *start;
    lb->end.x = lb->start.x + lb->magnitude * cosf( toRadians( lb->angle ) );
    lb->end.y = lb->start.y + lb->magnitude * sinf( toRadians( lb->angle ) );
}

void drawLightBeam( LightBeam *lb ) {
    DrawLineV( lb->start, lb->endDraw, lb->color );
}