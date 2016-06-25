#include <iostream>
#include <cstdlib>
#include "infnumber.h"
#include "lista.h"

using namespace std;

InfNumber * InfCreate(){
    InfNumber * inf=new InfNumber;
    inf->numbers=cria_lista();
    return inf;
}

InfNumber * InfCreateTwo(char *str){
	InfNumber * x= InfCreate();
	int i=0;
	while(str[i++] != '\0'){
		char c=str[i-1];
		insere_fim(x->numbers, atoi(&c));
	}
	return x;
}

InfNumber * InfConvert(const char *str){
    InfNumber * inf=InfCreate();
    int i=0;
    if(str[0] == '-'){
       inf->numbers->sinal='-';
       i++;
    }else{
        inf->numbers->sinal='+';
    }
    while(str[i++] != '\0'){
        const char aux=str[i-1];
        insere_fim(inf->numbers, atoi(&aux));
    }
    return inf;
}

bool InfCompare(InfNumber *a, InfNumber *b){
	Node * aux=a->numbers->primeiro;
	Node * aux2=b->numbers->primeiro;
	while(aux != NULL && aux2 != NULL){
		if(aux->valor != aux2->valor){
			return false;
		}
		aux=aux->prox;
		aux2=aux2->prox;
	}
	
	return true;
}

bool InfBigger(InfNumber *a, InfNumber *b){
    int a_tam=0,b_tam=0;
    for(Node * aux=a->numbers->primeiro ;  aux != NULL ; aux=aux->prox,a_tam++){}
    for(Node * aux=b->numbers->primeiro ;  aux != NULL ; aux=aux->prox,b_tam++){}
    if(a_tam > b_tam)
        return true;
    if(b_tam < a_tam)
        return false;
    Node * aux=a->numbers->primeiro;
    Node * aux2=b->numbers->primeiro;
    while(true){
        if(aux->valor > aux2->valor)
            return true;
        if(aux2->valor > aux->valor)
            return false;
        aux=aux->prox;
        aux2=aux2->prox;
        if(aux == NULL && aux2 == NULL)
			return true;
    }
    return false;
}

InfNumber * InfSum(InfNumber * a, InfNumber * b){
    InfNumber * c=InfCreate();
    Node * aux1=a->numbers->ultimo;
    Node * aux2=b->numbers->ultimo;
	char siga=a->numbers->sinal;
	char sigb=b->numbers->sinal;
    
    if(a->numbers->sinal == '+' && b->numbers->sinal == '+'){
		bool adicionou=false;
		while(aux1 != NULL && aux2 != NULL){
			int qualquer=aux1->valor + aux2->valor;
			if(adicionou && aux1 != NULL){
				aux1->valor--;
				adicionou=false;
			}
			if(qualquer >=10){
	 			qualquer-=10;
				if(aux1->ant!=NULL){
					aux1->ant->valor++;
					adicionou=true;
				}else{
					if(aux2->ant != NULL){
						aux2->ant->valor++;
					}else{
						insere_inicio(c->numbers,1);
						break;
					}
				}
			}
			insere_inicio(c->numbers,qualquer);
			aux1=aux1->ant;
			aux2=aux2->ant;
		}
		while(aux1 != NULL){
			insere_inicio(c->numbers, aux1->valor);
			aux1=aux1->ant;
		}
		while(aux2 != NULL){
			insere_inicio(c->numbers, aux2->valor);
			aux2=aux2->ant;
		}
		return c;
	}else{
		char c;
		if(InfBigger(a,b))
			c=a->numbers->sinal;
		else
			c=b->numbers->sinal;
			
		a->numbers->sinal='+';
		b->numbers->sinal='+';
		
		InfNumber * res;
		if(InfBigger(a,b))
			res=InfSub(a,b);
		else{
			res=InfSub(b,a);
		}
		res->numbers->sinal=c;
		a->numbers->sinal=siga;
		b->numbers->sinal=sigb;
		return res;
	}
}

InfNumber * InfSub(InfNumber * a, InfNumber * b){
	InfNumber * c=InfCreate();
	Node * aux1=a->numbers->ultimo;
	Node * aux2=b->numbers->ultimo;

	char siga=a->numbers->sinal;
	char sigb=b->numbers->sinal;

	if(a->numbers->sinal == '+' && b->numbers->sinal == '+'){
			bool adicionou=false;
			c->numbers->sinal=a->numbers->sinal;
			while(aux1 != NULL && aux2 != NULL){
				if(aux1->valor < aux2->valor){
					aux1->valor+=10;
					if(aux2->ant != NULL){
						aux2->ant->valor+=1;
					}else{
						aux2->ant=cria_node(1);
						adicionou=true;
                    }
                }
                insere_inicio(c->numbers, aux1->valor - aux2->valor);
				if(adicionou){
					Node * temp=a->numbers->primeiro;
					a->numbers->primeiro=a->numbers->primeiro->prox;
					adicionou=false;
				}
                aux1=aux1->ant;
                aux2=aux2->ant;
			}
            while(aux1 != NULL){
                insere_inicio(c->numbers, aux1->valor);
                aux1=aux1->ant;
            }
            while(aux2 != NULL){
                insere_inicio(c->numbers, aux2->valor);
                aux2=aux2->ant;
            }
            a->numbers->sinal=siga;
			b->numbers->sinal=sigb;
            return c;
    }else{
		if(a->numbers->sinal == '-' && b->numbers->sinal == '+'){
			a->numbers->sinal='+';
			b->numbers->sinal='+';
			InfNumber * res=InfSum(a,b);
			InfPrint(res);
			res->numbers->sinal='-';
			a->numbers->sinal=siga;
			b->numbers->sinal=sigb;
			return res;
		}
		char c;
		if(InfBigger(a,b))
			c=a->numbers->sinal;
		else
			c=b->numbers->sinal;
		a->numbers->sinal='+';
		b->numbers->sinal='+';

		InfNumber * res;
		if(InfBigger(a,b))
			res=InfSum(a,b);
		else
			res=InfSum(b,a);
		res->numbers->sinal=c;
		a->numbers->sinal=siga;
		b->numbers->sinal=sigb;
		return res;
	}
}

int quant(InfNumber * n){
	int counter=0;
	for(Node * aux = n->numbers->primeiro ; aux != NULL ; aux=aux->prox){
		counter++;
	}
	return counter;
}

/*
InfNumber * InfMult(InfNumber * a, InfNumber * b){
	InfNumber * c=InfCreate();
	int a_len=quant(a);
	int b_len=quant(b);
	
	int sinalx=a->numbers->sinal;
	int sinaly=b->numbers->sinal;

	Node * nodeb=b->numbers->ultimo;

	InfNumber ** lista=(InfNumber **)new InfNumber[b_len];
	for(int i=0 ; i<b_len ; i++){
		lista[i]=InfCreate();
	}

	bool vai_um=false;
	int valor_vai_um=0;

	for(int i=0 ;i<b_len && nodeb != NULL ; i++){
		int x=nodeb->valor;
		for(Node * aux=a->numbers->ultimo ; aux != NULL ; aux=aux->ant)
		{
			int result=x*aux->valor;
			if(vai_um){
				result+=valor_vai_um;
				valor_vai_um=0;
				vai_um=false;
			}
			if (result>=10)
			{
				vai_um=true;
				valor_vai_um=result/10;
				result=result%10;
			}
			insere_inicio(lista[i]->numbers,result);
		}
		if(valor_vai_um > 0){
			insere_inicio(lista[0]->numbers, valor_vai_um);	
		}
		nodeb=nodeb->ant;

	}

	for(int i=0 ; i<b_len ; i++){
		for(int k=i ; k>0 ;k--){
			insere_fim(lista[i]->numbers, 0);
		}
	}

	insere_fim(c->numbers, 0);

	for(int i=0 ; i<b_len ; i++){
		c->numbers->sinal='+';
		lista[i]->numbers->sinal='+';
		InfNumber * x=InfSum(c,lista[i]);
		c->numbers=x->numbers;
	}
	if((sinalx == '+' && sinaly == '-') || (sinalx == '-') && sinaly == '+' ){
		c->numbers->sinal='-';
	}else{
		c->numbers->sinal='+';
	}

	return c;
}
*/

InfNumber * InfMult(InfNumber * a, InfNumber * b){
	if(InfBigger(b,a))
		return InfMult(b,a);

	InfNumber * c=InfCreate();
	int a_len=quant_esq(a);
	int b_len=quant_esq(b);
	
	int sinalx=a->numbers->sinal;
	int sinaly=b->numbers->sinal;

	Node * nodeb=b->numbers->ultimo;

	InfNumber ** lista=(InfNumber **)new InfNumber[b_len];
	for(int i=0 ; i<b_len ; i++){
		lista[i]=InfCreate();
	}

	bool vai_um=false;
	int valor_vai_um=0;

	for(int i=0 ;i<b_len && nodeb != NULL ; i++){
		int x=nodeb->valor;
		for(Node * aux=a->numbers->ultimo ; aux != NULL ; aux=aux->ant)
		{
			int result=x*aux->valor;
			if(vai_um){
				result+=valor_vai_um;
				valor_vai_um=0;
				vai_um=false;
			}
			if (result>=10)
			{
				vai_um=true;
				valor_vai_um=result/10;
				result=result%10;
			}
			insere_inicio(lista[i]->numbers,result);
		}
		if(valor_vai_um > 0){
			insere_inicio(lista[0]->numbers, valor_vai_um);	
		}
		nodeb=nodeb->ant;

	}

	for(int i=0 ; i<b_len ; i++){
		for(int k=i ; k>0 ;k--){
			insere_fim(lista[i]->numbers, 0);
		}
	}

	insere_fim(c->numbers, 0);

	for(int i=0 ; i<b_len ; i++){
		c->numbers->sinal='+';
		lista[i]->numbers->sinal='+';
		InfNumber * x=InfSum(c,lista[i]);
		c->numbers=x->numbers;
	}
	if((sinalx == '+' && sinaly == '-') || (sinalx == '-') && sinaly == '+' ){
		c->numbers->sinal='-';
	}else{
		c->numbers->sinal='+';
	}

	return c;
}

void InfPrint(InfNumber * n){
	std::cout<<n->numbers->sinal;
	for(Node * aux = n->numbers->primeiro ; aux != NULL ; aux=aux->prox){
		std::cout<<aux->valor;
	}
	std::cout<<std::endl;
}
