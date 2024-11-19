#include "expressao.h"
#include "expressao.c"

int main() {
    Expressao expr;
    expr.posFixa[0] = '\0';
    char conta[100];

    while (1) {
        printf("Digite a continuação da conta ou 'f' para sair: ");
        fgets(conta, sizeof(conta), stdin);
        conta[strcspn(conta, "\n")] = '\0';

        if (strcmp(conta, "f") == 0) {
            printf("Programa encerrado.\n");
            break;
        }

        if (expr.posFixa[0] != '\0') {
            strcat(expr.posFixa, " ");
        }
        strcat(expr.posFixa, conta);

        char *infixaResult = getFormaInFixa(expr.posFixa);
        strcpy(expr.inFixa, infixaResult);
        free(infixaResult);

        expr.Valor = getValor(expr.posFixa);

        printf("Posfixa: %s\n", expr.posFixa);
        printf("Infixa: %s\n", expr.inFixa);
        printf("Valor: %.2f\n\n", expr.Valor);
    }

    return 0;
}
