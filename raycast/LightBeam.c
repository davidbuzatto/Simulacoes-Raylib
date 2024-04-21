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
    //DrawLineV( lb->start, lb->end, Fade( WHITE, 0.5 ) );
    DrawLineV( lb->start, lb->endDraw, lb->color );
}

void printLightBeam( LightBeam *lb, int id ) {

    TraceLog( 
        LOG_INFO, 
        "%d - %.2f %.2f %.2f %.2f",
        id,
        lb->endDraw.x,
        lb->endDraw.y,
        lb->angle,
        slope( &lb->start, &lb->end )
    );

}