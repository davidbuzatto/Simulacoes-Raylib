#include "raylib.h"
#include "Poligono.h"

void desenharPoligono( Poligono *poligono ) {
    DrawPolyLinesEx( 
        poligono->centro, 
        poligono->quantidadeLados, 
        poligono->raio,
        poligono->angulo, poligono->larguraTraco,
        poligono->cor );
}