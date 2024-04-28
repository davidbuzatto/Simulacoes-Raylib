#include <math.h>

#include "Bar.h"
#include "utils.h"
#include "raylib.h"

void updateBar( Bar *bar ) {

    bar->percent = ( 1.0f + sinf( DEG2RAD * bar->angle ) ) / 2.0f;
    
    /*bar->angle += bar->angleStep;
    if ( bar->angle > 360.0f ) {
        bar->angle = 0.0f;
    }*/

    bar->angle -= bar->angleStep;
    if ( bar->angle < 0.0f ) {
        bar->angle = 360.0f;
    }

}

void drawBar( Bar *bar ) {

    int height = lerp( bar->minHeight, bar->maxHeight, bar->percent );
    
    int rightUpX = bar->x + bar->width / 2;
    int rightUpY = bar->y - height / 2 - bar->topDiagonalHeight / 2;

    int leftUpX = bar->x - bar->width / 2;
    int leftUpY = rightUpY;

    int rightDownX = rightUpX;
    int rightDownY = bar->y + height / 2 - bar->topDiagonalHeight / 2;
    
    int leftDownX = leftUpX;
    int leftDownY = rightDownY;

    int topX = bar->x;
    int topY = bar->y - height / 2 - bar->topDiagonalHeight;

    int topUpX = bar->x;
    int topUpY = bar->y - height / 2;

    int topDownX = bar->x;
    int topDownY = bar->y + height / 2;

    Vector2 pointsR[] = {
        { rightUpX, rightUpY },     // direita cima
        { topUpX, topUpY },         // meio cima
        { rightDownX, rightDownY }, // direita baixo
        { topDownX, topDownY }      // meio baixo
    };

    Vector2 pointsL[] = {
        { topUpX, topUpY },         // meio cima
        { leftUpX, leftUpY },       // esquerda cima
        { topDownX, topDownY },     // meio baixo
        { leftDownX, leftDownY }    // esquerda baixo
    };

    Vector2 pointsT[] = {
        { rightUpX, rightUpY },    // direita
        { topX, topY },            // cima
        { topUpX, topUpY },        // baixo
        { leftUpX, leftUpY }       // esquerda
    };

    // colors
    Color darkerColor = ColorBrightness( bar->color, -0.5 );
    Color lighterColor = ColorBrightness( bar->color, 0.5 );

    DrawTriangleStrip( pointsR, 4, darkerColor );
    DrawTriangleStrip( pointsL, 4, lighterColor );
    DrawTriangleStrip( pointsT, 4, bar->color );
    
}