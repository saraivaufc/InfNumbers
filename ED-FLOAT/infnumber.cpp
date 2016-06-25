#include <iostream>
#include <cstdio>
#include <cstdarg>
#include <cstdlib>
#include <string.h>
#include <sstream>
#include "infnumber.h"
#include "lista.h"

using namespace std;

InfNumber * InfCopy(InfNumber * valor){
	InfNumber *aux=InfCreate();
	for(Node * node=valor->numbers->primeiro;node != NULL ; node=node->prox){
		insere_fim(aux->numbers , node->valor);
	}
	aux->virgula=valor->virgula;
	aux->numbers->sinal=valor->numbers->sinal;
	aux->numbers->tam=valor->numbers->tam;
	return aux;
}

InfNumber * InfCreate(){
    InfNumber * inf=new InfNumber;
    inf->numbers=cria_lista();
    inf->virgula=0;
    return inf;
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
    i=0;
    while(str[i] != '\0'){
        const char aux=str[i];
        if(aux == ',' || aux == '.'){
			inf->virgula=i;
		}else{
			insere_fim(inf->numbers, atoi(&aux));
		}
		i++;
	}
	//~ if(inf->virgula == 0){
		//~ inf->virgula=quant_esq(inf);
	//~ }
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

bool InfBig(InfNumber *a, InfNumber *b){
	Node * aux_a=a->numbers->primeiro;
	Node * aux_b=b->numbers->primeiro;
	while(aux_a != NULL && aux_b != NULL){
		if(aux_a->valor > aux_b->valor)
			return true;
		if(aux_a->valor < aux_b->valor)
			return false;
		aux_a=aux_a->prox;
		aux_b=aux_b->prox;
	}
	return false;
}

bool is_sinal(const char s[]){
	if((int)strlen(s) == 1 && (s[0] == '+' || s[0] == '-' || s[0] == '*')){
		return true;
	}
	return false;
}

void InfSetsinal(char sinal , InfNumber * a){
	if(sinal == '-')
		a->numbers->sinal='-';
	else
		a->numbers->sinal='+';
}

char * floatToString(float f) {
	char buf[48];
	snprintf (buf, sizeof(buf), "%f", f);
	char * teste=(char *) malloc(strlen(buf) * sizeof(char));
	strcpy(teste,buf);
	return teste;
}

void InfAddZeros(InfNumber * a, InfNumber * b){
	int tam_a=quant_esq(a);
	int tam_b=quant_esq(b);
	if(tam_a > tam_b && b->virgula > 0){
		int i=0;
		while(i++ < (tam_a-tam_b)){
			insere_inicio(b->numbers, 0);
			b->virgula++;
		}
	}else if(tam_a < tam_b && a->virgula > 0){
		int i=0;
		while(i++ < (tam_b-tam_a)){
			insere_inicio(a->numbers, 0);
			a->virgula++;
		}
	}
	tam_a=quant_dir(a);
	tam_b=quant_dir(b);
	
	int i=0;
	if(tam_a == 0){
		a->virgula=quant_esq(a);
		insere_fim(a->numbers, 0);
		tam_a++;
	}
	if(tam_b == 0){
		b->virgula=quant_esq(b);
		insere_fim(b->numbers, 0);
		tam_b++;
	}
	
	if(tam_a > tam_b){
		while(i++ < (tam_a-tam_b) && b->virgula>0){
			insere_fim(b->numbers, 0);
			tam_b++;
		}
	}else if(tam_b > tam_a){
		while(i++ < (tam_b-tam_a) && a->virgula>0){
			insere_fim(a->numbers, 0);
		}
	}
}

InfNumber * InfSum(InfNumber * x, InfNumber * y){
	if(InfBig(y,x)){
		return InfSum(y,x);
	}
	InfNumber * a=InfCopy(x);
	InfNumber * b=InfCopy(y);

	char sinalx=x->numbers->sinal;
	char sinaly=y->numbers->sinal;
	
	InfAddZeros(a, b);
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
				c->virgula++;
				adicionou=false;
			}
			if(qualquer >=10){
	 			qualquer-=10;
				if(aux1->ant!=NULL){
					aux1->ant->valor++;
					c->virgula++;
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
		if(c->virgula == 0){
			c->virgula=a->virgula;
		}
		return c;
	}else{
		char c;
		if(InfBig(a,b))
			c=a->numbers->sinal;
		else
			c=b->numbers->sinal;
			
		a->numbers->sinal='+';
		b->numbers->sinal='+';
		
		InfNumber * res;
		if(InfBig(a,b))
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

InfNumber * InfSub(InfNumber * x, InfNumber * y){
	
	InfNumber * a=InfCopy(x);
	InfNumber * b=InfCopy(y);
	
	InfAddZeros(a, b);
	
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
					c->virgula++;
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
			if(c->virgula == 0){
				if(InfBig(a,b)){
					c->virgula=a->virgula;
				}else{
					c->virgula=b->virgula;
				}
			}
            return c;
    }else{
		if(a->numbers->sinal == '-' && b->numbers->sinal == '+'){
			a->numbers->sinal='+';
			b->numbers->sinal='+';
			InfNumber * res=InfSum(a,b);
			res->numbers->sinal='-';
			a->numbers->sinal=siga;
			b->numbers->sinal=sigb;
			
			return res;
		}
		char c;
		if(InfBig(a,b))
			c=a->numbers->sinal;
		else
			c=b->numbers->sinal;
		a->numbers->sinal='+';
		b->numbers->sinal='+';
		InfNumber * res;
		if(InfBig(a,b))
			res=InfSum(a,b);
		else
			res=InfSum(b,a);
		res->numbers->sinal=c;
		a->numbers->sinal=siga;
		b->numbers->sinal=sigb;

		return res;
	}
}

int quant_esq(InfNumber * n){
	int counter=0;
	if(n->virgula == 0){
		for(Node * aux = n->numbers->primeiro ; aux != NULL; aux=aux->prox){
			counter++;
		}
		return counter;
	}
	int i=0;
	for(Node * aux = n->numbers->primeiro ; aux != NULL && i++ <n->virgula ; aux=aux->prox){
		counter++;
	}
	return counter;
}
int quant_dir(InfNumber * n){
	if(n->virgula == 0)
		return 0;
	
	int counter=0;
	int i=1;
	for(Node * aux = n->numbers->primeiro ; aux != NULL; aux=aux->prox){
			if(i > n->virgula && n->virgula != 0)
				counter++;
			i++;
	}
	return counter;
}

InfNumber * InfMult(InfNumber * X, InfNumber * Y){
	InfNumber * a=InfCopy(X);
	InfNumber * b=InfCopy(Y);
	
	InfNumber * c=InfCreate();
	int a_len=quant_esq(a);
	int b_len=quant_esq(b);

	int a_len_dir=quant_dir(a);
	int b_len_dir=quant_dir(b);
	
	if(a_len_dir>b_len_dir){
		while(a_len_dir-- > 0){
			insere_fim(b->numbers, 0);
		}
	}else{
		while(b_len_dir-- > 0){
			insere_fim(a->numbers, 0);
		}
	}
	
	int sinalx=a->numbers->sinal;
	int sinaly=b->numbers->sinal;

	Node * nodeb=b->numbers->ultimo;

	InfNumber ** lista=(InfNumber **)new InfNumber[b->numbers->tam];
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
	c->virgula=(quant_esq(a) + quant_esq(b))-1;
	return c;
}


void InfPrint(InfNumber * n){
	std::cout<<n->numbers->sinal;
	int virgula=n->virgula;
	int i=1;
	for(Node * aux = n->numbers->primeiro ; aux != NULL ; aux=aux->prox){
		std::cout<<aux->valor;
		if(i++ == virgula)
			cout<<",";
	}
	std::cout<<std::endl;
}
