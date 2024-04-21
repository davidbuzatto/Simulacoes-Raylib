/**
 * @file utils.c
 * @author Prof. Dr. David Buzatto
 * @brief Utilitary functions implementation.
 * 
 * @copyright Copyright (c) 2024
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "raylib.h"
#include "utils.h"
#include "LightBeam.h"
#include "Obstacle.h"

double toRadians( double degrees ) {
    return degrees * PI / 180.0;
}

double toDegrees( double radians ) {
    return radians * 180.0 / PI;
}

// https://en.wikipedia.org/wiki/Line%E2%80%93line_intersection
bool getIntersectionPoint( LightBeam *lb, Obstacle *ob, Vector2 *intersectionPoint ) {

    float x1 = lb->start.x;
    float x2 = lb->end.x;
    float x3 = ob->start.x;
    float x4 = ob->end.x;

    float y1 = lb->start.y;
    float y2 = lb->end.y;
    float y3 = ob->start.y;
    float y4 = ob->end.y;

    float d = ((x1-x2)*(y3-y4)-(y1-y2)*(x3-x4));

    if ( d != 0 ) {

        float t = ((x1-x3)*(y3-y4)-(y1-y3)*(x3-x4))/d;
        float u = -((x1-x2)*(y1-y3)-(y1-y2)*(x1-x3))/d;

        if ( t >= 0.0 && t <= 1.0 && u >= 0.0 && u <= 1.0 ) {

            /*Vector2 vt = { 
                .x = x1 + t*(x2-x1),
                .y = y1 + t*(y2-y1),
            };*/

            Vector2 vu = { 
                .x = x3 + u*(x4-x3),
                .y = y3 + u*(y4-y3),
            };

            *intersectionPoint = vu;
            return true;

        }

    }

    return false;

}

bool containsPoint( Obstacle *ob, Vector2 *point ) {
    float xs = ob->start.x < ob->end.x ? ob->start.x : ob->end.x;
    float xe = ob->start.x < ob->end.x ? ob->end.x : ob->start.x;
    float ys = ob->start.y < ob->end.y ? ob->start.y : ob->end.y;
    float ye = ob->start.y < ob->end.y ? ob->end.y : ob->start.y;
    return point->x >= xs && point->x <= xe &&
           point->y >= ys && point->y <= ye;
}