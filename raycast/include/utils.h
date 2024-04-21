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