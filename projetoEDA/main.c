/*****************************************************************//**
 * \file   main.c
 * \brief  Ficheiro Main do programa AINDA EM DESENVOLVIMENTO/INCORRETO
 *
 * \author Vitor Moreira 31553
 * \date   30 de Mar�o 2025
 *********************************************************************/
#include "antenas.h"
#include <stdio.h>

int main() {
    // Carregar antenas
    Antena* lista = CarregarAntenasDoFicheiro("C://Users//vitor//Desktop//projetoEDA//projetoEDA//projetoEDA//antenas.txt");
    if (!lista) {
        printf("Erro ao carregar o ficheiro!\n");
        return 1;
    }

    // Imprimir matriz com nefastos
    //printf("Matriz com localiza��es nefastas:\n");
    //ImprimirMatrizComNefastos(lista, 12, 12);

    // Libertar mem�ria
    while (lista) {
        Antena* temp = lista;
        lista = lista->prox; 
        free(temp);
    }

    return 0;
}