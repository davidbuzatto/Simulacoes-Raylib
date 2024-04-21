#include "Obstacle.h"
#include "raylib.h"

void drawObstacle( Obstacle *ob ) {
    DrawLineV( ob->start, ob->end, ob->color );
}