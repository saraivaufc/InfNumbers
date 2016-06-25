#include <iostream>
#include <cstdlib>
#include "pilha.h"

using namespace std;


Pilha * create_pilha(){
	Pilha * p=new Pilha;
	p->tamanho=0;
	p->primeiro=NULL;
	return p;
}

Node_Pilha * create_Node_Pilha(InfNumber * valor){
	Node_Pilha * n=new Node_Pilha;
	n->valor=valor;
	n->prox=NULL;
	return n;
}

void push(Pilha *p, InfNumber * valor){
	InfNumber * teste=InfCopy(valor);
	teste->virgula=valor->virgula;
	teste->numbers->sinal=valor->numbers->sinal;
	Node_Pilha * n=create_Node_Pilha(teste);
	n->prox=p->primeiro;
	p->primeiro=n;
	p->tamanho++;
	return;
}

InfNumber * pop(Pilha * p){
	if(p->tamanho == 0){
		return NULL;
	}
	InfNumber * valor=InfCopy(p->primeiro->valor);
	valor->virgula=p->primeiro->valor->virgula;
	valor->numbers->sinal=p->primeiro->valor->numbers->sinal;
	valor->numbers->tam=p->primeiro->valor->numbers->tam;
	p->primeiro=p->primeiro->prox;
	p->tamanho--;
	return valor;
}

void mostra_pilha(Pilha * p){
	for(Node_Pilha * aux=p->primeiro ; aux != NULL ; aux=aux->prox){
		InfPrint(aux->valor);
	}
}
