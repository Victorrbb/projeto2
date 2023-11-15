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