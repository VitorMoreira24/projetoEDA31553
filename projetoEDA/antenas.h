/*****************************************************************//**
 * \file   antenas.h
 * \brief  Ficheiro .h com todos os dados relacionados com as antenas
 * 
 * \author Vitor Moreira 31553
 * \date   30 de Mar�o 2025
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
  * \param frequencia - Frequ�ncia da antena ex: 'A', 'B'
  * \param linha - Linha da matriz
  * \param coluna - Coluna da matriz
  * \param prox - Aponta para a pr�xima antena
  * 
  *********************************************************************/
typedef struct Antena {
    char frequencia;       // Ex: 'A', 'B'
    int linha, coluna;     // Posi��o na matriz
    struct Antena* prox;   // Pr�xima antena
} Antena;

// Prot�tipos das fun��es no ficheiro antenas.c
Antena* CriaAntena(char frequencia, int linha, int coluna);
Antena* InsereOrdenado(Antena* inicio, Antena* novo);
Antena* RemoveAntena(Antena* inicio, int linha, int coluna);
Antena* ProcuraAntena(Antena* inicio, int linha, int coluna);
//void DestroiListaAntenas(Antena** h);
