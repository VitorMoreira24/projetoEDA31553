#include "antenas.h"

#pragma region Criar Antena

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

Antena* ProcuraAntena(Antena* inicio, int linha, int coluna) {
	Antena* aux = inicio;
	while (aux && aux->linha < linha) {//linha v e no dei baixo
		aux = aux->prox;
	}
	if (aux && aux->linha == linha){
		while (aux && aux->coluna < coluna) {//linha v e no dei baixo
			aux = aux->prox;
		}
		if (aux && aux->coluna == coluna) {
			if (aux->frequencia != '.')return aux;	//valor encontrado
		}
	}
	return NULL;
}

#pragma endregion
#pragma region Carregar Antenas Do Ficheiro

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
