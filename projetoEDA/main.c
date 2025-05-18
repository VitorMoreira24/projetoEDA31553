/*****************************************************************//**
 * \file   main.c
 * \brief  Ficheiro Main do programa AINDA EM DESENVOLVIMENTO/INCORRETO
 *
 * \author Vitor Moreira 31553
 * \date   30 de Março 2025
 *********************************************************************/
#define _CRT_SECURE_NO_WARNINGS
#include "antenas.h"
#include <stdio.h>

void menu() {
    printf("\n=== MENU ===\n");
    printf("1. Inserir antena\n");
    printf("2. Remover antena\n");
    printf("3. Procurar antena\n");
    printf("4. Mostrar matriz\n");
    printf("5. Mostrar matriz com efeitos nefastos\n");
    printf("6. Carregar antenas de ficheiro\n");
    printf("0. Sair\n");
    printf("Escolha: ");
}

int main() {
    Antena* lista = NULL;
    nefastos* listaNefastos = NULL;
    int opcao;

    do {
        menu();
        scanf("%d", &opcao);

        switch (opcao) {
        case 1: {
            int linha, coluna;
            char freq;
            printf("Digite a linha: ");
            scanf("%d", &linha);
            printf("Digite a coluna: ");
            scanf("%d", &coluna);
            printf("Digite a frequencia: ");
            scanf(" %c", &freq);

            Antena* nova = CriaAntena(coluna, linha, freq);
            lista = InsereOrdenado(lista, nova);
            printf("Antena inserida com sucesso!\n");
            break;
        }
        case 2: {
            int linha, coluna;
            printf("Linha: "); scanf("%d", &linha);
            printf("Coluna: "); scanf("%d", &coluna);
            lista = RemoveAntena(lista, linha, coluna);
            printf("Antena removida!\n");
            break;
        }
        case 3: {
            int linha, coluna;
            printf("Linha: "); scanf("%d", &linha);
            printf("Coluna: "); scanf("%d", &coluna);
            Antena* encontrada = ProcuraAntena(lista, linha, coluna);
            if (encontrada) {
                printf("Antena encontrada: %c\n", encontrada->frequencia);
            }
            else {
                printf("Antena nao encontrada.\n");
            }
            break;
        }
        case 4: {
            if (lista != NULL) {
                mostrarMatrizAntenas(lista);
            }
            else {
                printf("Erro: Lista de antenas vazia. Carregue ou insira primeiro.\n");
            }
            break;
        }
        case 5: {
            if (listaNefastos != NULL) {
                libertarListaNefasto(listaNefastos);
            }
            listaNefastos = calcularNefastos(lista);
            mostrarMatrizNefastos(lista, listaNefastos);
            break;
        }
        case 6: {
            Antena* carregadas = CarregarAntenasDoFicheiro("antenas.txt");
            if (carregadas) {
                // Liberta lista anterior se houver
                while (lista) {
                    Antena* temp = lista;
                    lista = lista->prox;
                    free(temp);
                }
                lista = carregadas;
                printf("Antenas carregadas com sucesso.\n");
            }
            else {
                printf("Erro ao carregar antenas do ficheiro.\n");
            }
            break;
        }
        case 0: {
            printf("Saindo...\n");
            break;
        }
        default:
            printf("Opção inválida.\n");
        }
    } while (opcao != 0);

    // Libertar memória
    while (lista) {
        Antena* temp = lista;
        lista = lista->prox;
        free(temp);
    }

    if (listaNefastos != NULL) {
        libertarListaNefasto(listaNefastos);
    }

    return 0;
}
