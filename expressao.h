#ifndef EXPRESSAO_H
#define EXPRESSAO_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

typedef struct {
    char posFixa[512];
    char inFixa[512];
    float Valor;
} Expressao;

typedef struct {
    char *items[512];
    int top;
} Lista;

int push(Lista *lista, char *valor);
char *pop(Lista *lista);
char *getFormaInFixa(char *Str);
float getValor(char *Str);

#endif