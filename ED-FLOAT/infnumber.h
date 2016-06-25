#ifndef OPERACOES_H
#define OPERACOES_H

#include "lista.h"

struct InfNumber{
	Lista * numbers;
	int virgula;
};

bool InfCompare(InfNumber *a, InfNumber *b);
void InfPrint(InfNumber * n);
int quant_dir(InfNumber * n);
int quant_esq(InfNumber * n);
char * floatToString(float f);
InfNumber * InfCopy(InfNumber * valor);
void InfSetsinal(char sinal , InfNumber * a);
bool is_sinal(const char * s);
bool InfBig(InfNumber *a, InfNumber *b);

InfNumber * InfCreate();
InfNumber * InfConvert(const char *str);
InfNumber * InfSum(InfNumber * a, InfNumber * b);
InfNumber * InfSub(InfNumber * a, InfNumber * b);
InfNumber * InfMult(InfNumber * a, InfNumber * b);

#endif
