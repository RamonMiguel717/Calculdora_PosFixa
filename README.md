# Calculdora_PosFixa
O objetivo deste projeto é criar uma calculadora que compreenda o modelo de calculo PosFixo e retorne também uma String Infixa 

## Planejamento das funções

### Bibliotecas
Além das bibliotecas padrões da linguagem C, achei cabível a implementação das bibliotecas 
  - string.h
  - ctype.h
  - math.h

### Structs

Além da struct Experssão que o professor pediu que fosse colocada no codigo, decidi por utilizar uma Struct auxiliar 

typedef struct {
    char *items[512];
    int top;
} Lista;

Decidi utilizar este modelo para facilitar a manipulação de informações ao decorrer do código.

# Funções

Foram requisitadas algumas funções que não poderiam ter suas extruturas modificadas, o que dificultou um pouco o desenvolvimento do projeto, entretanto, 
foi possível finalizar o codigo com a criação de somente mais duas funções auxíliares com o objetivo de manipular as informações inseridas pelo usuário, como na linguagem C não existem funções
push e pull, criei-as para realizar tal função:

void push(Lista *lista, char *valor) {
    lista->items[++lista->top] = valor;
}
char *pop(Lista *lista) {
    return lista->items[lista->top--];
}

O codigo funciona na seguinte sequência:

### Main 
Iniciando no documento main.c, o codigo inicializa variáveis locais e pilhas para o funcionamento das funções posteriores.
Fiz o uso de uma estrutura de repetição infinita com *While(1)* para a entrada de dados na calculadora, caso o usuário deseje sair da repetição é necessário que o mesmo digite "f" para sair.


    while (1) {
        printf("Digite a continuação da conta ou 'f' para sair: ");
        fgets(conta, sizeof(conta), stdin);
        conta[strcspn(conta, "\n")] = '\0';

        if (strcmp(conta, "f") == 0) {
            printf("Programa encerrado.\n");
            break;
        }

Sendo que as informações são salvas na variavel **conta**, que posteriormente será concatenada em ***expr.posFixa*** para reutilização em funções posteriores.

Após todos estes processos, será chamada a primeira função base

### getFormaInFixa

Sendo uma função de organização, decidi juntar todas as validações e criar um sistema para tirar os espaços inseridos na sequência e organiza-los
e após algumas séries de validações organizar a conta no modelo (operador1, sinal, operador2) utilizando o comando **sprintf** como foi sugerido pelo professor.

```
                char *opr2 = pop(&lista);
                char *opr1 = pop(&lista);

                char *expression = (char *)malloc(strlen(opr1) + strlen(opr2) + 4);
                sprintf(expression, "(%s %c %s)", opr1, Str[i], opr2);

                free(opr1);
                free(opr2);

                push(&lista, expression);
```
Ao final fazemos o uso do comando pop para enviar a lista organizada e armazenar a variável na **expr.inFixa** com o uso de strcpy de volta no main.

### getValor

Após algumas validações e organização do codigo tive que fazer uma concatenação de **else if** para realizar as operações de:
  - Seno
  - Cosseno
  - Tangente
  - Log base 10

Já que no modelo de validação que eu tinha realizado, não era possivel fazer a leitura de mais de um caractere inserido como simbolo matemático. E após isso fiz a verificação dos caracteres utilizando switch/case:

```
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

                push(&lista, (char *)malloc(16));
                snprintf(lista.items[lista.top], 16, "%f", result);
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
```
Após todo o calculo, a conta é armazenada em **expr.Valor** e finaliza printando todas as informações armazenadas até o momento.

# Testes
Os testes foram realizados para validar o funcionamento correto da calculadora, garantindo que os seguintes cenários sejam tratados adequadamente:

### Casos de teste básicos

***Entrada: 3 4 +***

Resultado esperado:

Forma infixa: (3 + 4)

Valor: 7

Entrada: 10 2 ^

***Resultado esperado:***

Forma infixa: (10 ^ 2)

Valor: 100

Entrada: 6 3 /

***Resultado esperado:***

Forma infixa: (6 / 3)

Valor: 2

### Casos de erro

Divisão por zero:

Entrada: 5 0 /

***Resultado esperado: Mensagem de erro "Erro: Divisão por zero.".***

Operador inválido:

Entrada: 4 5 ?

***Resultado esperado: Mensagem de erro "Erro: Operador desconhecido '?'.".***

### Casos avançados
Operações trigonométricas:

Entrada: 30 sin

***Resultado esperado:***

Forma infixa: sin(30)

Valor (em radianos): 0.5.

### Múltiplas operações:

Entrada: 3 4 + 2 *

***Resultado esperado:***

Forma infixa: ((3 + 4) * 2)

Valor: 14.

***Os testes confirmaram que o programa é robusto e lida bem com entradas válidas e inválidas. Os resultados foram armazenados em arquivos de log para referência futura.***
