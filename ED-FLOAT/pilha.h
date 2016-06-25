#ifndef PILHA_H
#define PILHA_H

#include "infnumber.h"

typedef struct NodeP{
	InfNumber * valor;
	struct NodeP * prox;
}Node_Pilha;

struct Pilha{
	int tamanho;
	Node_Pilha * primeiro;
};

Pilha * create_pilha();
Node_Pilha * create_node(InfNumber* valor);
void push(Pilha *p, InfNumber * valor);
InfNumber * pop(Pilha * p);
void mostra_pilha(Pilha * p);

#endif
