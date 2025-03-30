#include "antenas.h"
#include <stdio.h>

int main() {
    // Carregar antenas
    Antena* lista = CarregaAntenasFicheiro("C://Users//vitor//Desktop//projetoEDA//projetoEDA//projetoEDA//antenas.txt");
    if (!lista) {
        printf("Erro ao carregar o ficheiro!\n");
        return 1;
    }

    // Imprimir matriz com nefastos
    printf("Matriz com localizações nefastas:\n");
    ImprimirMatrizComNefastos(lista, 12, 12);

    // Liberar memória
    while (lista) {
        Antena* temp = lista;
        lista = lista->prox;
        free(temp);
    }

    return 0;
}