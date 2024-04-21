#include <stdlib.h>
#include <math.h>

#include "LightSource.h"
#include "LightBeam.h"
#include "Obstacle.h"
#include "utils.h"
#include "raylib.h"

LightSource *createLightSource( int lightBeamQuantity, Color color ) {

    LightSource *ls = (LightSource*) malloc( sizeof( LightSource ) );
    ls->pos = (Vector2){ GetScreenWidth()/2, GetScreenHeight()/2 };
    ls->lightBeams = (LightBeam*) malloc( lightBeamQuantity * sizeof( LightBeam ) );
    ls->lightBeamQuantity = lightBeamQuantity;
    ls->color = color;

    int mag = 1000;
    float currentAngle = 0;
    float step = 360.0 / lightBeamQuantity;

    for ( int i = 0; i < lightBeamQuantity; i++ ) {
        ls->lightBeams[i] = (LightBeam){
            .start = { 0, 0 },
            .end = { 0, 0 },
            .endDraw = { 0, 0 },
            .angle = currentAngle,
            .magnitude = mag,
            //.color = ColorFromHSV( currentAngle, 1, 1 )
            .color = ls->color
        };
        updateLightBeam( &ls->lightBeams[i], &ls->pos );
        currentAngle += step;
    }

    return ls;

}

void destroyLightSource( LightSource *ls ) {
    free( ls->lightBeams );
    free( ls );
}

void updateLightSource( LightSource *ls ) {
    
    ls->pos = GetMousePosition();
    //ls->pos.x += GetRandomValue( -1, 1 );
    //ls->pos.y += GetRandomValue( -1, 1 );

    for ( int i = 0; i < ls->lightBeamQuantity; i++ ) {
        updateLightBeam( &ls->lightBeams[i], &ls->pos );
    }

}

void drawLightSource( LightSource *ls ) {
    for ( int i = 0; i < ls->lightBeamQuantity; i++ ) {
        drawLightBeam( &(ls->lightBeams[i]) );
    }
    DrawCircleV( ls->pos, 5, ls->color );
}

