#ifndef LISTA_H
#define LISTA_H

typedef struct Node_{
    int valor;
    struct Node_ * prox;
    struct Node_ * ant;
}Node;

struct Lista{
    int tam;
    char sinal;
    Node * primeiro;
    Node * ultimo;
};

Node * cria_node(int x);

Lista * cria_lista();

void insere_inicio(Lista * l, int valor);

void insere_fim(Lista * l, int valor);

void imprimir_lista(Lista *l);

int * remove_inicio(Lista * l);

int * remove_fim(Lista * l);

void destroi(Lista * l);
#endif
