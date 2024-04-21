#include <stdlib.h>
#include <math.h>

#include "LightSource.h"
#include "LightBeam.h"
#include "Obstacle.h"
#include "utils.h"
#include "raylib.h"

LightSource *createLightSource( int lightBeamQuantity, Color color, float startAngle, int obstacleCount ) {

    LightSource *ls = (LightSource*) malloc( sizeof( LightSource ) );
    //ls->pos = (Vector2){ GetScreenWidth()/2, GetScreenHeight()/2 };
    ls->pos = (Vector2){ 0, 0 };
    ls->lightBeamQuantity = lightBeamQuantity;
    ls->lightBeams = (LightBeam*) malloc( lightBeamQuantity * sizeof( LightBeam ) );
    ls->color = color;
    ls->collidedPoints = (Vector2*) malloc( obstacleCount * sizeof(Vector2) );

    int magnitude = 1000;
    float currentAngle = startAngle;
    float step = 360.0 / lightBeamQuantity;

    for ( int i = 0; i < lightBeamQuantity; i++ ) {
        ls->lightBeams[i] = (LightBeam){
            .start = { 0, 0 },
            .end = { 0, 0 },
            .endDraw = { 0, 0 },
            .angle = currentAngle,
            .magnitude = magnitude,
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
    free( ls->collidedPoints );
    free( ls );
}

void updateLightSource( LightSource *ls ) {
    
    ls->pos = GetMousePosition();
    
    /*ls->pos.x += perlin2d( ls->pos.x, ls->pos.x, 0.1, 4 );
    ls->pos.y += perlin2d( ls->pos.x, ls->pos.y, 0.1, 4 );*/

    /*ls->pos.x += Perlin_Get2d( ls->pos.x, ls->pos.x, 0.1, 4 );
    ls->pos.y += Perlin_Get2d( ls->pos.x, ls->pos.y, 0.1, 4 );*/

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

