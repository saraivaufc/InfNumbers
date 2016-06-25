#include <iostream>
#include <cstdio>
#include <cstdarg>
#include <cstdlib>
#include <string.h>
#include <sstream>
#include "lista.h"
#include "infnumber.h"
#include "pilha.h"

using namespace std;

InfNumber *total=NULL;

int main(){
	Pilha * p=create_pilha();
	bool cal=false;
	while(true){
		string c;
		system("clear");
		cout<<"|Pilha|\n";
		mostra_pilha(p);
		cout<<"\n|Entrada|:";
		cin>>c;
		if( c.compare("q") == 0)
			break;
			
		const char * c2 = c.c_str();
		InfNumber *a, *b;

		int i;
		if(is_sinal(c.c_str()))
			i=0;
		else
			i=1;
		switch(c2[i])
		{
			case '+':
					{
						a=pop(p);
						b=pop(p);
						total = InfSum(a,b);
						total->numbers->sinal='+';
						push(p,total);
					}
					break;
			case '-':
				{
					a=pop(p);
					b=pop(p);
					if(InfBig(a,b)){
						total = InfSub(a,b);
						total->numbers->sinal='-';
					}else{
						total = InfSub(b,a);
					}
					push(p,total);
				}
				break;
			case '*':
					{
						a=pop(p);
						b=pop(p);
						if(InfBig(a,b)){
							total = InfMult(a,b);
						}else{
							total = InfMult(b,a);
						}
						total->numbers->sinal='+';
						InfNumber * casa=InfCopy(total);
						push(p,casa);
					}
					break;
			case 'q':
					cal=false;
					break;
			default:
				InfNumber * novo=InfCopy(InfConvert(c2));
					InfSetsinal(c2[0],novo);
					push(p,novo);
					break;
		}
	}
	cout<<"Total Final:";
	InfPrint(pop(p));
}



