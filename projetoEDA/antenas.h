/*****************************************************************//**
 * \file   antenas.h
 * \brief  Ficheiro .h com todos os dados relacionados com as antenas
 * 
 * \author Vitor Moreira 31553
 * \date   30 de Março 2025
 *********************************************************************/
#pragma once
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
 /*****************************************************************//**
  * \brief Struct que representa uma antena
  *
  * \param frequencia - Frequência da antena ex: 'A', 'B' , '.' , etc
  * \param linha - Linha da matrizes
  * \param coluna - Coluna da matriz
  * \param prox - Aponta para a próxima antena
  * 
  *********************************************************************/
typedef struct Antena {
    char frequencia;       // Ex: 'A', 'B'
    int linha, coluna;     // Posição na matriz
    struct Antena* prox;   // Próxima antena
} Antena;


/*****************************************************************//**
 * \brief Struct que representa nefastos
 *
 * \param x - Coordenada x
 * \param y - Coordenada y
 * \param prox - Aponta para o próximo nefasto
 *********************************************************************/
typedef struct nefastos {
	int x, y;
	struct nefastos* prox;
}nefastos;

extern int MAX_COLUNAS;
extern int MAX_LINHAS;

// Protótipos das funções no ficheiro antenas.c
Antena* CriaAntena(char frequencia, int linha, int coluna);
Antena* InsereOrdenado(Antena* inicio, Antena* novo);
Antena* RemoveAntena(Antena* inicio, int linha, int coluna);
Antena* ProcuraAntena(Antena* inicio, int linha, int coluna);
Antena* CarregarAntenasDoFicheiro(const char* nome_ficheiro);
nefastos* criarEfeitoNefasto(int x, int y);
nefastos* calcularNefastos(Antena* lista);
void mostrarMatrizAntenas(Antena* lista);
void mostrarMatrizNefastos(Antena* lista_antenas, nefastos* lista_nefastos);
void libertarListaNefasto(nefastos* lnefasto);
//void DestroiListaAntenas(Antena** h);
