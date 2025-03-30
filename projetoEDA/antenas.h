#pragma once
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

typedef struct Antena {
    char frequencia;       // Ex: 'A', 'B'
    int linha, coluna;     // Posição na matriz
    struct Antena* prox;   // Próxima antena
} Antena;

// Protótipos das funções
Antena* CriaAntena(char frequencia, int linha, int coluna);
Antena* InsereOrdenado(Antena* inicio, Antena* novo);
Antena* RemoveAntena(Antena* inicio, int linha, int coluna);
Antena* ProcuraAntena(Antena* inicio, int linha, int coluna);
//void DestroiListaAntenas(Antena** h);
