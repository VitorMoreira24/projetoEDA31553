/*****************************************************************//**
 * \file   antenas.c
 * \brief  Ficheiro com todas as funções relacionadas com as antenas
 * 
 * \author Vitor Moreira 31553
 * \date   30 de Março 2025
 *********************************************************************/
#include "antenas.h"

#pragma region Criar Antena
 /*****************************************************************//**
  * \brief Função que cria uma antena
  *
  * \param freq - Frequência da antena
  * \param linha - Linha da matriz
  * \param coluna - Coluna da matriz
  *
  * \return Retorna a antena criada
  *********************************************************************/
Antena* CriaAntena(char freq, int linha, int coluna) {
	Antena* aux = (Antena*)malloc(sizeof(Antena));
	if (aux != NULL) {
		aux->frequencia = freq;
		aux->linha = linha;
		aux->coluna = coluna;
		aux->prox = NULL;
	}
	return aux;
}
#pragma endregion 

#pragma region Insere Ordenado
/*****************************************************************//**
 * \brief Função que insere uma antena ordenada
 *
 * \param inicio - Inicio da lista
 * \param novo - Antena a inserir
 *
 * \return Retorna a lista com a antena inserida
 *********************************************************************/
Antena* InsereOrdenado(Antena* inicio, Antena* novo) {
	//Validações
	if (novo == NULL) return inicio;
	//se a lista for vazia
	if (inicio == NULL || novo->linha < inicio->linha || 
	(novo->linha == inicio->linha && novo->coluna < inicio->coluna))
	{
		inicio = novo; //rever
		return inicio;
	}
	//restantes situações
	//procurar a posição correta
	Antena* aux = inicio;
	Antena* aux2 = aux;

	while (aux != NULL && (aux->linha < novo->linha ||
	(aux->linha == novo->linha && aux->coluna < novo->coluna)))
	{
		aux2 = aux;
		aux = aux->prox;
	}
	//verfica se insere no fim
	if (aux->linha < novo->linha || aux->coluna < novo->coluna)
		aux->prox = novo;
	else {				//insere entre elementos
		aux2->prox = novo;
		novo->prox = aux;
	}
	return inicio;
}
#pragma endregion

#pragma region Remove Antena
/*****************************************************************//**
 * \brief Função que remove uma antena
 *
 * \param inicio - Inicio da lista
 * \param linha - Linha da matriz
 * \param coluna - Coluna da matriz
 *
 * \return Retorna a lista com a antena removida
 *********************************************************************/
Antena* RemoveAntena(Antena* inicio, int linha, int coluna) {
	if (inicio == NULL) return NULL;			//Lista vazia

	if (inicio->linha == linha && inicio->coluna == coluna) {		//remove no inicio da lista
		Antena* aux = inicio;
		inicio = inicio->prox;
		free(aux);
	}
	else
	{
		Antena* aux = inicio;
		Antena* auxAnt = aux;
		while (aux != NULL && (aux->linha != linha || aux->coluna != coluna)){	//procura para remover
			auxAnt = aux;
			aux = aux->prox;
		}
		if (aux != NULL) {					//se encontrou, remove
			auxAnt->prox = aux->prox;
			free(aux);
		}
	}
	return inicio;
}
#pragma endregion

#pragma region Procura Antena
/*****************************************************************//**
 * \brief Função que procura uma antena
 *
 * \param inicio - Inicio da lista
 * \param linha - Linha da matriz
 * \param coluna - Coluna da matriz
 *
 * \return Retorna a antena encontrada
 *********************************************************************/
Antena* ProcuraAntena(Antena* inicio, int linha, int coluna) {
	/*(Antena * aux = inicio;
	while (aux && aux->linha < linha) {
		aux = aux->prox;
	}
	if (aux && aux->linha == linha){
		while (aux && aux->coluna < coluna) {
			aux = aux->prox;
		}
		if (aux && aux->coluna == coluna) {
			if (aux->frequencia != '.')return aux;	
		}
	}
	return NULL;*/
	Antena* aux = inicio;
	while (aux != NULL) {
		if (aux->linha == linha && aux->coluna == coluna) {
			return aux;
		}
		aux = aux->prox;
	}
	return NULL;
}
#pragma endregion

#pragma region Carregar Antenas Do Ficheiro
/*****************************************************************//**
 * \brief Função que carrega as antenas de um ficheiro
 *
 * \param nome_ficheiro - Nome do ficheiro
 *
 * \return Retorna a lista de antenas
 *********************************************************************/
Antena* CarregarAntenasDoFicheiro(const char* nome_ficheiro) { //ver
	FILE* fp = fopen(nome_ficheiro, "r");
	if (fp == NULL) {
		printf("Erro ao abrir\n");
		return NULL;
	}

	Antena* lista = NULL;
	Antena* ultima = NULL;
	char linha[256];
	int y = 0;

	while (fgets(linha, sizeof(linha), fp)) {
		int comp = strlen(linha);
		if (linha[comp - 1] == '\n') {
			linha[comp - 1] = '\0';
			comp--;
		}
		for (int x = 0; x < comp; x++) {
			char c = linha[x];
			if (c != '.') {
				Antena* ant = CriarAntena(x, y, c);
				if (lista == NULL) {
					lista = ant;
				}
				else {
					ultima->prox = ant;
				}
				ultima = ant;
			}
		}
		y++;
	}
	fclose(fp);
	return lista;
}
#pragma endregion
