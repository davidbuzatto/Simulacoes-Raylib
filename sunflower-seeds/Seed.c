#include <math.h>
#include "raylib.h"
#include "Seed.h"
#include "utils.h"

void updateSeed( Seed *seed, float distance ) {

    float speed = seed->speed * GetFrameTime();

    Vector2 vel = {
        .x = speed * cosf( DEG2RAD * seed->angle ),
        .y = speed * sinf( DEG2RAD * seed->angle ),
    };

    seed->pos.x += vel.x;
    seed->pos.y += vel.y;

    float t = distance / seed->maxDistanceToGrow;
    t = t > 1 ? 1 : t;
    seed->radius = lerp( seed->minRadius, seed->maxRadius, t );

    t = distance / seed->maxDistanceToChangeColor;
    t = t > 1 ? 1 : t;
    seed->color = ColorFromHSV( lerp( 85.0f, 40.0f, t ), 1, 1 );
    //seed->color = ColorFromHSV( lerp( 30, 255, t ), 1, 1 );

}

void drawSeed( Seed *seed ) {
    DrawCircleV( seed->pos, seed->radius, seed->color );
}