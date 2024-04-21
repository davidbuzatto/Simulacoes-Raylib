/**
 * @file utils.h
 * @author Prof. Dr. David Buzatto
 * @brief Utilitary function and constant declarations.
 * 
 * @copyright Copyright (c) 2024
 */
#pragma once

#include <stdbool.h>
#include "raylib.h"
#include "LightBeam.h"
#include "Obstacle.h"

double toRadians( double degrees );
double toDegrees( double radians );

bool getIntersectionPoint( LightBeam *lb, Obstacle *ob, Vector2 *intersectionPoint );
bool containsPoint( Obstacle *ob, Vector2 *point );
float slope( Vector2 *p1, Vector2 *p2 );

// https://gist.github.com/nowl/828013
int noise2(int x, int y);
float lin_inter(float x, float y, float s);
float smooth_inter(float x, float y, float s);
float noise2d(float x, float y);
float perlin2d(float x, float y, float freq, int depth);
double Perlin_Get2d(double x, double y, double freq, int depth);