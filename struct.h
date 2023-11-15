#include "stdio.h"

typedef struct Cliente {
    char nome[100];
    char cpf[12];
    int tipo;
    double valor_entrada;
    int senha;
} Cliente;