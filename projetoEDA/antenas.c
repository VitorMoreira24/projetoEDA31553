/*****************************************************************//**
 * \file   antenas.c
 * \brief  Ficheiro com todas as funções relacionadas com as antenas
 * 
 * \author Vitor Moreira 31553
 * \date   30 de Março 2025
 *********************************************************************/
#include "antenas.h"
int MAX_COLUNAS = 0;
int MAX_LINHAS = 0;

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
Antena* CriaAntena(char coluna, int linha, int freq) {
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
	if (novo == NULL) return inicio;

	if (ProcuraAntena(inicio, novo->linha, novo->coluna) != NULL) {
		free(novo);
		return inicio;
	}
	if (inicio == NULL) {
		inicio = novo;
		return inicio;
	}
	if ((novo->linha < inicio->linha) || (novo->linha == inicio->linha && novo->coluna < inicio->coluna)) {
		novo->prox = inicio;
		inicio = novo;
		return inicio;
	}

	Antena* atual = inicio;
	Antena* ant = atual;

	while ((atual->linha < novo->linha || (atual->linha == novo->linha && atual->coluna < novo->coluna)) && atual->prox != NULL) {

		ant = atual;
		atual = atual->prox;

	}
	if ((atual->linha == novo->linha && atual->coluna > novo->coluna)) {
		novo->prox = atual;
		ant->prox = novo;
		return inicio;

	}
	if (atual->linha < novo->linha && atual->coluna < novo->coluna) {
		atual->prox = novo;
		return inicio;

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

#pragma region MostrarAntena
/*****************************************************************//**
 * \brief Função que mostra a lista de antenas
 *
 * \param inicio - Inicio da lista
 *********************************************************************/
void mostrarMatrizAntenas(Antena* lista) {
	printf("\nMatriz de Antenas (%dx%d):\n", MAX_LINHAS, MAX_COLUNAS);

	for (int l = 0; l < MAX_LINHAS; l++) {
		for (int c = 0; c < MAX_COLUNAS; c++) {
			Antena* ant = ProcuraAntena(lista, l, c);
			if (ant != NULL) {
				printf("%c ", ant->frequencia);
			}
			else {
				printf(". ");
			}
		}
		printf("\n");
	}
}

#pragma
#pragma region Nefastos
/**
 * .
 * criarEfeitoNefasto
 * \param x
 * \param y
 * \return
 */
nefastos* criarEfeitoNefasto(int x, int y) {
	nefastos* novo = (nefastos*)malloc(sizeof(nefastos));
	if (novo != NULL) {
		novo->x = x;
		novo->y = y;
		novo->prox = NULL;
	}
	return novo;
}

/**
 * .
 * calcularEfeitoNefastoFinal
 * \param lista
 * \return
 */
nefastos* calcularNefastos(Antena* lista) {
	nefastos* nefasto = NULL;
	Antena* atual = lista;


	while (atual != NULL) {
		Antena* comparar = atual->prox;

		while (comparar != NULL) {
			if (atual->frequencia == comparar->frequencia) {

				int diff_linha = comparar->linha - atual->linha;
				int diff_coluna = comparar->coluna - atual->coluna;


				int nefasto_linha = comparar->linha + diff_linha;
				int nefasto_coluna = comparar->coluna + diff_coluna;


				if (nefasto_linha >= 0 && nefasto_coluna >= 0 && nefasto_linha < MAX_LINHAS && nefasto_coluna < MAX_COLUNAS) {//rever
					nefastos* novo = criarEfeitoNefasto(nefasto_linha, nefasto_coluna);
					novo->prox = nefasto;
					nefasto = novo;
				}

				nefasto_linha = atual->linha - diff_linha;
				nefasto_coluna = atual->coluna - diff_coluna;

				if (nefasto_linha >= 0 && nefasto_coluna >= 0 && nefasto_linha < MAX_LINHAS && nefasto_coluna < MAX_COLUNAS) {
					nefastos* novo2 = criarEfeitoNefasto(nefasto_linha, nefasto_coluna);
					novo2->prox = nefasto;
					nefasto = novo2;
				}
			}
			comparar = comparar->prox;
		}
		atual = atual->prox;
	}

	return nefasto;
}


/**
 * .
 * mostrarMatrizComNefastos
 * Exibe a matriz mostrando antenas e pontos nefastos
 * \param lista_antenas Lista de antenas
 * \param lista_nefastos Lista de pontos nefastos
 */
void mostrarMatrizNefastos(Antena* lista_antenas, nefastos* lista_nefastos) {
	printf("\nMatriz com Efeitos Nefastos (%dx%d):\n", MAX_LINHAS, MAX_COLUNAS); //rever
	for (int l = 0; l < MAX_LINHAS; l++) {
		for (int c = 0; c < MAX_COLUNAS; c++) {
			Antena* ant = ProcuraAntena(lista_antenas, l, c);

			if (ant != NULL) {
				printf("%c ", ant->frequencia);
			}
			else {
				nefastos* n = lista_nefastos;
				int verificarnefasto = 0;

				while (n != NULL && verificarnefasto == 0) {
					if (n->x == l && n->y == c) {
						verificarnefasto = 1;
					}
					n = n->prox;
				}

				if (verificarnefasto) {
					printf("# ");
				}
				else {
					printf(". ");
				}
			}
		}
		printf("\n");
	}
}

/**
 * .
 * libertarListaNefasto
 * Função para libertar a memoria
 * \param lista
 */
void libertarListaNefasto(nefastos* lnefasto) {
	nefastos* atual = lnefasto;

	while (atual != NULL) {
		nefastos* proximo = atual->prox;
		free(atual);
		atual = proximo;
	}
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
		return NULL;
	}

	Antena* lista = NULL;
	Antena* ultima = NULL;
	char linha[256];
	int x = 0;
	MAX_COLUNAS = 0;

	while (fgets(linha, sizeof(linha), fp)) {
		int comp = strlen(linha);
		if (linha[comp - 1] == '\n' || linha[comp - 1] == '\r') {
			linha[comp - 1] = '\0';
			comp--;
		}
		if (comp > MAX_COLUNAS) {
			MAX_COLUNAS = comp;
		}
		for (int c = 0; c < comp; c++) {
			char freq = linha[c];
			if (freq != '.') {
				Antena* ant = CriaAntena(c, x, freq); 
				if (lista == NULL) {
					lista = ant;
				}
				else {
					ultima->prox = ant;
				}
				ultima = ant;
			}
		}
		x++;
	}
	MAX_LINHAS = x;
	fclose(fp);
	return lista;
}
#pragma endregion

//ADICIONAR MOSTRAR MATRIZ

//ADICIONAR NEFASTOS2

//MOSTRAR MATRIZ COM NEFASTOS

//LIBERTARNEFASTOS
