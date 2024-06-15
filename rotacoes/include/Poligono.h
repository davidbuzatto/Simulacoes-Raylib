#pragma once

#include "raylib.h"

typedef struct Poligono {
    Vector2 centro;
    int quantidadeLados;
    float raio;
    float angulo;
    float larguraTraco;
    float velocidadeAngular;
    Color cor;
} Poligono;

void desenharPoligono( Poligono *poligono );