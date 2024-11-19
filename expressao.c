#include "expressao.h"


void push(Lista *lista, char *valor) {
    lista->items[++lista->top] = valor;
}

char *pop(Lista *lista) {
    return lista->items[lista->top--];
}

char *getFormaInFixa(char *Str) {
    Lista lista;
    lista.top = -1;

    for (int i = 0; Str[i] != '\0'; i++) {
        if (isspace(Str[i])) continue;

        if (isdigit(Str[i])) {
            char numBuffer[16];
            int j = 0;
            while (isdigit(Str[i]) && Str[i] != '\0') numBuffer[j++] = Str[i++];
            numBuffer[j] = '\0';
            i--;

            char *operand = (char *)malloc(strlen(numBuffer) + 1);
            strcpy(operand, numBuffer);
            push(&lista, operand);
        } else if (strncmp(Str + i, "sen", 3) == 0) {
            if (lista.top < 0) {
                printf("Erro: Operando insuficiente para 'sen'.\n");
                exit(EXIT_FAILURE);
            }
            char *operand = pop(&lista);
            char *expression = (char *)malloc(strlen(operand) + 8);
            sprintf(expression, "(sen %s)", operand);
            free(operand);
            push(&lista, expression);
            i += 2;
        } else if (strncmp(Str + i, "cos", 3) == 0) {
            if (lista.top < 0) {
                printf("Erro: Operando insuficiente para 'cos'.\n");
                exit(EXIT_FAILURE);
            }
            char *operand = pop(&lista);
            char *expression = (char *)malloc(strlen(operand) + 8);
            sprintf(expression, "(cos %s)", operand);
            free(operand);
            push(&lista, expression);
            i += 2;
        } else if (strncmp(Str + i, "tg", 2) == 0) {
            if (lista.top < 0) {
                printf("Erro: Operando insuficiente para 'tg'.\n");
                exit(EXIT_FAILURE);
            }
            char *operand = pop(&lista);
            char *expression = (char *)malloc(strlen(operand) + 7);
            sprintf(expression, "(tg %s)", operand);
            free(operand);
            push(&lista, expression);
            i += 1;
        } else if (strncmp(Str + i, "raiz", 4) == 0) {
            if (lista.top < 0) {
                printf("Erro: Operando insuficiente para 'raiz'.\n");
                exit(EXIT_FAILURE);
            }
            char *operand = pop(&lista);
            char *expression = (char *)malloc(strlen(operand) + 10);
            sprintf(expression, "(raiz %s)", operand);
            free(operand);
            push(&lista, expression);
            i += 3;
        } else {
            if (lista.top < 1) {
                printf("Erro: Operandos insuficientes para operador '%c'.\n", Str[i]);
                exit(EXIT_FAILURE);
            }
            char *opr2 = pop(&lista);
            char *opr1 = pop(&lista);
            char *expression = (char *)malloc(strlen(opr1) + strlen(opr2) + 4);
            sprintf(expression, "(%s %c %s)", opr1, Str[i], opr2);
            free(opr1);
            free(opr2);
            push(&lista, expression);
        }
    }

    if (lista.top != 0) {
        printf("Erro: Expressão inválida.\n");
        exit(EXIT_FAILURE);
    }

    return pop(&lista);
}

float getValor(char *Str) {
    Lista lista;
    lista.top = -1;

    for (int i = 0; Str[i] != '\0'; i++) {
        if (isspace(Str[i])) continue;

        if (isdigit(Str[i])) {
            char numBuffer[16];
            int j = 0;
            while (isdigit(Str[i]) && Str[i] != '\0') numBuffer[j++] = Str[i++];
            numBuffer[j] = '\0';
            i--;

            char *numStr = (char *)malloc(strlen(numBuffer) + 1);
            strcpy(numStr, numBuffer);
            push(&lista, numStr);
        } else if (strncmp(Str + i, "sen", 3) == 0) {
            if (lista.top < 0) {
                printf("Erro: Operando insuficiente para 'sen'.\n");
                exit(EXIT_FAILURE);
            }
            char *operadorStr = pop(&lista);
            float operador = atof(operadorStr);
            free(operadorStr);
            push(&lista, (char *)malloc(16));
            snprintf(lista.items[lista.top], 16, "%f", sin(operador));
            i += 2;
        } else {
            printf("Operação não implementada.\n");
            exit(EXIT_FAILURE);
        }
    }

    if (lista.top != 0) {
        printf("Erro: Elementos restantes na pilha após cálculo.\n");
        exit(EXIT_FAILURE);
    }

    float final = atof(pop(&lista));
    free(lista.items[lista.top + 1]);
    return final;
}
