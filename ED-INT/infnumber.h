#ifndef OPERACOES_H
#define OPERACOES_H

#include "lista.h"

struct InfNumber{
    Lista * numbers;
};

InfNumber * InfCreate();
InfNumber * InfCreateTwo(char *str);
InfNumber * InfConvert(const char *str);

bool InfCompare(InfNumber *a, InfNumber *b);
void InfPrint(InfNumber * n);
bool InfBigger(InfNumber *a, InfNumber *b);
InfNumber * InfSum(InfNumber * a, InfNumber * b);
InfNumber * InfSub(InfNumber * a, InfNumber * b);
InfNumber * InfMult(InfNumber * a, InfNumber * b);

#endif
