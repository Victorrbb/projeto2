#include <stdio.h>
#include "funcaoo.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    // Declaração de variável para armazenar a opção do menu
    int opcao;

    // Loop do menu principal
    do {
        // Chama a função que exibe o menu
        menu();

        // Solicitação e leitura da opção escolhida pelo usuário
        scanf("%d", &opcao);

        // Estrutura switch para lidar com diferentes opções do menu
        switch (opcao) {
            case 1:
                // Chama a função para criar um novo cliente
                criar_cliente();
                break;

            case 2:
                // Chama a função para apagar um cliente
                apagar_cliente();
                break;
            case 3:
                // Chama a função para listar todos os clientes
                listarClientes();
                break;
            case 4:
                // Chama a função para realizar um débito
                debito();
                break;
            case 5:
                // Chama a função para realizar um depósito
                deposito();
                break;
            case 6:
                // Chama a função de trasnferencia
                transferencia();
                break;