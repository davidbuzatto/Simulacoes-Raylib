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
#include <math.h>

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
                .y = y1 + t*(y2-y1)
            };*/

            Vector2 vu = { 
                .x = x3 + u*(x4-x3),
                .y = y3 + u*(y4-y3)
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

float slope( Vector2 *p1, Vector2 *p2 ) {
    return ( p2->y - p1->y ) / ( p2->x - p1->x );
}

// https://gist.github.com/nowl/828013
static int SEED = 0;
static int hash[] = {208,34,231,213,32,248,233,56,161,78,24,140,71,48,140,254,245,255,247,247,40,
                     185,248,251,245,28,124,204,204,76,36,1,107,28,234,163,202,224,245,128,167,204,
                     9,92,217,54,239,174,173,102,193,189,190,121,100,108,167,44,43,77,180,204,8,81,
                     70,223,11,38,24,254,210,210,177,32,81,195,243,125,8,169,112,32,97,53,195,13,
                     203,9,47,104,125,117,114,124,165,203,181,235,193,206,70,180,174,0,167,181,41,
                     164,30,116,127,198,245,146,87,224,149,206,57,4,192,210,65,210,129,240,178,105,
                     228,108,245,148,140,40,35,195,38,58,65,207,215,253,65,85,208,76,62,3,237,55,89,
                     232,50,217,64,244,157,199,121,252,90,17,212,203,149,152,140,187,234,177,73,174,
                     193,100,192,143,97,53,145,135,19,103,13,90,135,151,199,91,239,247,33,39,145,
                     101,120,99,3,186,86,99,41,237,203,111,79,220,135,158,42,30,154,120,67,87,167,
                     135,176,183,191,253,115,184,21,233,58,129,233,142,39,128,211,118,137,139,255,
                     114,20,218,113,154,27,127,246,250,1,8,198,250,209,92,222,173,21,88,102,219};

int noise2(int x, int y)
{
    /*int tmp = hash[(y + SEED) % 256];
    return hash[(tmp + x) % 256];*/
        int  yindex = (y + SEED) % 256;
    if (yindex < 0)
        yindex += 256;
    int  xindex = (hash[yindex] + x) % 256;
    if (xindex < 0)
        xindex += 256;
    const int  result = hash[xindex];
    return result;
}

float lin_inter(float x, float y, float s)
{
    return x + s * (y-x);
}

float smooth_inter(float x, float y, float s)
{
    return lin_inter(x, y, s * s * (3-2*s));
}

float noise2d(float x, float y)
{
    /*int x_int = x;
    int y_int = y;
    float x_frac = x - x_int;
    float y_frac = y - y_int;
    int s = noise2(x_int, y_int);
    int t = noise2(x_int+1, y_int);
    int u = noise2(x_int, y_int+1);
    int v = noise2(x_int+1, y_int+1);
    float low = smooth_inter(s, t, x_frac);
    float high = smooth_inter(u, v, x_frac);
    return smooth_inter(low, high, y_frac);*/
    const int  x_int = floor( x );
    const int  y_int = floor( y );
    const double  x_frac = x - x_int;
    const double  y_frac = y - y_int;
    const int  s = noise2( x_int, y_int );
    const int  t = noise2( x_int+1, y_int );
    const int  u = noise2( x_int, y_int+1 );
    const int  v = noise2( x_int+1, y_int+1 );
    const double  low = smooth_inter( s, t, x_frac );
    const double  high = smooth_inter( u, v, x_frac );
    const double  result = smooth_inter( low, high, y_frac );
    return result;
}

float perlin2d(float x, float y, float freq, int depth)
{
    float xa = x*freq;
    float ya = y*freq;
    float amp = 1.0;
    float fin = 0;
    float div = 0.0;

    int i;
    for(i=0; i<depth; i++)
    {
        div += 256 * amp;
        fin += noise2d(xa, ya) * amp;
        amp /= 2;
        xa *= 2;
        ya *= 2;
    }

    return fin/div;
}

double Perlin_Get2d(double x, double y, double freq, int depth)
{
    double  xa = x*freq;
    double  ya = y*freq;
    double  amp = 1.0;
    double  fin = 0;
    double  div = 0.0;
    for (int i=0; i<depth; i++)
    {
        div += 256 * amp;
        fin += noise2d( xa, ya ) * amp;
        amp /= 2;
        xa *= 2;
        ya *= 2;
    }
    return fin/div;
}