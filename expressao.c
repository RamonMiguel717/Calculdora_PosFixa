#include "expressao.h"

int push(Lista *lista, char *valor) {
    if (lista->top == 511) {
        printf("Erro: Pilha cheia.\n");
        return -1;
    }
    lista->items[++lista->top] = strdup(valor); 
    return 0;
}

char *pop(Lista *lista) {
    if (lista->top == -1) {
        printf("Erro: Pilha vazia.\n");
        return NULL;
    }
    char *valor = lista->items[lista->top];
    lista->top--;
    return valor;
}

char *getFormaInFixa(char *Str) {
    Lista lista;
    lista.top = -1;

    for (int i = 0; Str[i] != '\0'; i++) {
        if (isspace(Str[i])) continue;

        if (isdigit(Str[i])) {
            char numBuffer[511];
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
                
            }
            char *operand = pop(&lista);
            char *expression = (char *)malloc(strlen(operand) + 8);
            sprintf(expression, "(cos %s)", operand);
            free(operand);
            push(&lista, expression);
            i += 2;
 
        }else if (strncmp(Str + i, "log", 3) == 0) {
    if (lista.top < 0) {
        printf("Erro: Operando insuficiente para 'log'.\n");
        exit(EXIT_FAILURE);
    }
    char *operadorStr = pop(&lista);
    float operador = atof(operadorStr);
    free(operadorStr);

    if (operador <= 0) {
        printf("Erro: Logaritmo de número não positivo não permitido.\n");
        exit(EXIT_FAILURE);
    }

        push(&lista, (char *)malloc(511));
        snprintf(lista.items[lista.top], 511, "%f", log(operador)); 
        i += 2;
    }else if (strncmp(Str + i, "tg", 2) == 0) {
            if (lista.top < 0) {
                printf("Erro: Operando insuficiente para 'tg'.\n");
                
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
                
            }
            char *opr2 = pop(&lista);
            char *opr1 = pop(&lista);
            char *expression = (char *)malloc(strlen(opr1) + strlen(opr2) + 511);
            sprintf(expression, "(%s %c %s)", opr1, Str[i], opr2);
            free(opr1);
            free(opr2);
            push(&lista, expression);
        }
    }

    if (lista.top != 0) {
        printf("Erro: Expressão invalida.\n");
        
    }
    free(lista.items[lista.top + 1]); 

    return pop(&lista);
}

float getValor(char *Str) {
    Lista lista;
    lista.top = -1;

    for (int i = 0; Str[i] != '\0'; i++) {
        if (isspace(Str[i])) continue;

        if (isdigit(Str[i])) {
            char numBuffer[511];
            int j = 0;

            while (isdigit(Str[i]) && Str[i] != '\0') numBuffer[j++] = Str[i++];
            numBuffer[j] = '\0';
            i--;

            char *numStr = (char *)malloc(strlen(numBuffer) + 1);
            strcpy(numStr, numBuffer);
            push(&lista, numStr);
        } else {
            if (strncmp(Str + i, "sen", 3) == 0) {
                if (lista.top < 0) {
                    printf("Erro: Operando insuficiente para 'sen'.\n");
                    exit(EXIT_FAILURE);
                }
                char *operadorStr = pop(&lista);
                float operador = atof(operadorStr);
                free(operadorStr);
                push(&lista, (char *)malloc(511));
                snprintf(lista.items[lista.top], 511, "%f", sin(operador));
                i += 2; // Avance após "sen"
            } else if (strncmp(Str + i, "log", 3) == 0) {
    if (lista.top < 0) {
        printf("Erro: Operando insuficiente para 'log'.\n");
        exit(EXIT_FAILURE);
    }
    char *operadorStr = pop(&lista);
    float operador = atof(operadorStr);
    free(operadorStr);

    if (operador <= 0) {
        printf("Erro: Logaritmo de número não positivo não permitido.\n");
        exit(EXIT_FAILURE);
    }

        push(&lista, (char *)malloc(511));
        snprintf(lista.items[lista.top], 511, "%f", log(operador)); 
        i += 3;
        }else if (strncmp(Str + i, "cos", 3) == 0) {
                if (lista.top < 0) {
                    printf("Erro: Operando insuficiente para 'cos'.\n");
                    exit(EXIT_FAILURE);
                }
                char *operadorStr = pop(&lista);
                float operador = atof(operadorStr);
                free(operadorStr);
                push(&lista, (char *)malloc(511));
                snprintf(lista.items[lista.top], 511, "%f", cos(operador));
                i += 2;
            } else if (strncmp(Str + i, "tg", 2) == 0) {
                if (lista.top < 0) {
                    printf("Erro: Operando insuficiente para 'tg'.\n");
                    exit(EXIT_FAILURE);
                }
                char *operadorStr = pop(&lista);
                float operador = atof(operadorStr);
                free(operadorStr);
                push(&lista, (char *)malloc(511));
                snprintf(lista.items[lista.top], 511, "%f", tan(operador));
                i += 1;
            } else if (strncmp(Str + i, "raiz", 4) == 0) {
                if (lista.top < 0) {
                    printf("Erro: Operando insuficiente para 'raiz'.\n");
                    exit(EXIT_FAILURE);
                }
                char *operadorStr = pop(&lista);
                float operador = atof(operadorStr);
                free(operadorStr);
                if (operador < 0) {
                    printf("Erro: Raiz quadrada de número negativo não permitida.\n");
                    exit(EXIT_FAILURE);
                }
                push(&lista, (char *)malloc(511));
                snprintf(lista.items[lista.top], 511, "%f", sqrt(operador));
                i += 3;
            } else {
                if (lista.top < 1) {
                    printf("Erro: Operandos insuficientes para operador '%c'.\n", Str[i]);
                    exit(EXIT_FAILURE);
                }
                char *opr2Str = pop(&lista);
                char *opr1Str = pop(&lista);
                float opr2 = atof(opr2Str);
                float opr1 = atof(opr1Str);
                free(opr2Str);
                free(opr1Str);

                float result;
                switch (Str[i]) {
                    case '+': result = opr1 + opr2; break;
                    case '-': result = opr1 - opr2; break;
                    case '*': result = opr1 * opr2; break;
                    case '/':
                        if (opr2 == 0) {
                            printf("Erro: Divisão por zero.\n");
                            exit(EXIT_FAILURE);
                        }
                        result = opr1 / opr2;
                        break;
                    case '^': result = pow(opr1, opr2); break;
                    default:
                        printf("Erro: Operador desconhecido '%c'.\n", Str[i]);
                        exit(EXIT_FAILURE);
                }

                push(&lista, (char *)malloc(511));
                snprintf(lista.items[lista.top],511, "%f", result);
            }
        }
    }

    if (lista.top != 0) {
        printf("Erro: Elementos restantes na pilha após o cálculo.\n");
        exit(EXIT_FAILURE);
    }

    float final = atof(pop(&lista));
    free(lista.items[lista.top + 1]); // Libere o último elemento
    return final;
}
