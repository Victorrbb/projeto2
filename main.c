#include <stdio.h>
#include "function.h"
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
                // Chama a função para exibir o extrato
                extrato();
                break;
            case 7:
                // Chama a função para realizar uma transferência
                transferencia();
                break;
            case 8:
                // Mensagem de encerramento
                printf("Encerrado\n");
                break;
            default:
                // Mensagem para opção inválida
                printf("Opção inválida!\n");
                break;
        }
    } while (opcao != 8); // Continua o loop até que a opção escolhida seja 8 (Encerrar)

    // Retorna 0 para indicar que o programa foi executado com sucesso
    return 0;
}
