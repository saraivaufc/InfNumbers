#include <iostream>
#include <cstdlib>
#include "lista.h"

Node * cria_node(int x){
    Node * n=new Node;
    n->valor=x;
    n->prox=NULL;
    n->ant=
            NULL;
    return n;
}

Lista * cria_lista(){
    Lista * l=new Lista;
    l->tam=0;
    l->sinal='\0';
    l->primeiro=NULL;
    l->ultimo=NULL;
    return l;
}

void insere_inicio(Lista * l, int valor){
    Node * n=cria_node(valor);
    if(l->tam == 0){
        n->ant=l->primeiro;
        n->prox=l->primeiro;
        l->primeiro=n;
        l->ultimo=n;
    }else{
        n->ant=NULL;
        n->prox=l->primeiro;
        l->primeiro->ant=n;
        l->primeiro=n;
    }
    l->tam++;
    return;
}

void insere_fim(Lista * l, int valor){
    Node * n=cria_node(valor);
    if(l->tam == 0){
        insere_inicio(l,valor);
        return;
    }else{
        l->ultimo->prox=n;
        n->ant=l->ultimo;
        l->ultimo=n;
        l->tam++;
    }
    return;
}


int * remove_inicio(Lista * l){
    int * valor=new int;
    if(l->tam == 0){
        std::cout<<"Impossivel Remover,Lista Vazia..."<<std::endl;
        return NULL;
    }else{
        *valor=l->primeiro->valor;
        Node * aux=l->primeiro;
        l->primeiro=l->primeiro->prox;
        if(l->primeiro != NULL){
            l->primeiro->ant=NULL;
        }
        delete [] aux;
    }
    l->tam--;
    return valor;
}

int * remove_fim(Lista * l){
    int * valor=new int;
    if(l->tam == 0){
        std::cout<<"Impossivel Remover,Lista Vazia..."<<std::endl;
        return NULL;
    }else{
        *valor=l->ultimo->valor;
        Node * aux=l->ultimo;
        if(l->ultimo->ant == NULL){
            l->ultimo=NULL;
        }else{
            l->ultimo->ant->prox=NULL;
            l->ultimo=l->ultimo->ant;
        }
        delete [] aux;
    }
    l->tam--;
    return valor;
}


void destroi(Lista * l){
	while(l->primeiro != NULL){
		Node * aux=l->primeiro;
		l->primeiro=l->primeiro->prox;
		delete [] aux;
	}
}

void imprimir_lista(Lista *l){
    for(Node * aux=l->primeiro ; aux != NULL ; aux=aux->prox){
        std::cout<<"["<<aux->valor<<"]";
    }
    std::cout<<std::endl;
}
