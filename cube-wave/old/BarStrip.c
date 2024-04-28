#include <stdio.h>
#include <stdlib.h>

#include "BarStrip.h"
#include "Bar.h"
#include "raylib.h"

void createBarStrip( 
    BarStrip *newBarStrip,
    int x, int y, int barQuantity, 
    int barWidth, int barMinHeight, int barMaxHeight, int barTopDiagonalHeight,
    float angleStep, Color color, int te ) {

    newBarStrip->x = x;
    newBarStrip->y = y;
    newBarStrip->barWidth = barWidth;
    newBarStrip->barMinHeight = barMinHeight;
    newBarStrip->barMaxHeight = barMaxHeight;
    newBarStrip->barTopDiagonalHeight = barTopDiagonalHeight;
    newBarStrip->angleStep = angleStep;
    newBarStrip->color = color;
    newBarStrip->barQuantity = barQuantity;
    newBarStrip->bars = (Bar*) malloc( newBarStrip->barQuantity * sizeof( Bar ) );

    Bar *bars = newBarStrip->bars;

    int q;
    int k = 0;
    int mult = 20;

    if ( newBarStrip->barQuantity % 2 == 0 ) {

        q = newBarStrip->barQuantity / 2;

        for ( int i = 0; i < q; i++ ) {
            int base = k+1;
            int xOffset = i == 0 ? ( (i+1) * barWidth ) / 2 : (i+1) * barWidth - barWidth / 2;
            bars[k++] = (Bar){
                .x = x - xOffset,
                .y = y,
                .width = barWidth,
                .minHeight = barMinHeight,
                .maxHeight = barMaxHeight,
                .topDiagonalHeight = barTopDiagonalHeight,
                .percent = 0,
                .angle = base * mult + te,
                .angleStep = angleStep,
                .color = color
            };
            bars[k++] = (Bar){
                .x = x + xOffset,
                .y = y,
                .width = barWidth,
                .minHeight = barMinHeight,
                .maxHeight = barMaxHeight,
                .topDiagonalHeight = barTopDiagonalHeight,
                .percent = 0,
                .angle = base * mult + te,
                .angleStep = angleStep,
                .color = color
            };
        }

    } else {

        q = newBarStrip->barQuantity / 2 + 1;

        for ( int i = 0; i < q; i++ ) {
            if ( i == 0 ) {
                bars[k++] = (Bar){
                    .x = x,
                    .y = y,
                    .width = barWidth,
                    .minHeight = barMinHeight,
                    .maxHeight = barMaxHeight,
                    .topDiagonalHeight = barTopDiagonalHeight,
                    .percent = 0,
                    .angle = te,
                    .angleStep = angleStep,
                    .color = color
                };
            } else {
                int base = k+1;
                bars[k++] = (Bar){
                    .x = x - i * barWidth,
                    .y = y,
                    .width = barWidth,
                    .minHeight = barMinHeight,
                    .maxHeight = barMaxHeight,
                    .topDiagonalHeight = barTopDiagonalHeight,
                    .percent = 0,
                    .angle = base * mult + te,
                    .angleStep = angleStep,
                    .color = color
                };
                bars[k++] = (Bar){
                    .x = x + i * barWidth,
                    .y = y,
                    .width = barWidth,
                    .minHeight = barMinHeight,
                    .maxHeight = barMaxHeight,
                    .topDiagonalHeight = barTopDiagonalHeight,
                    .percent = 0,
                    .angle = base * mult + te,
                    .angleStep = angleStep,
                    .color = color
                };
            }
        }

    }

}

void destroyBarStrip( BarStrip *bs ) {
    free( bs->bars );
    free( bs );
}

void destroyBarsFromBarStrip( BarStrip *bs ) {
    free( bs->bars );
}

void updateBarStrip( BarStrip *bs ) {
    for ( int i = 0; i < bs->barQuantity; i++ ) {
        updateBar( &bs->bars[i] );
    }
}

void drawBarStrip( BarStrip *bs ) {
    for ( int i = 0; i < bs->barQuantity; i++ ) {
        drawBar( &bs->bars[i] );
    }
}
