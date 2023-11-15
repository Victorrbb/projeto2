#include "funcao.h"

#include <dirent.h>
#include <malloc.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>
//menu para mostrar o que fazer
void menu(){
    printf("Bem vindo ao banco\n");
    printf("\nescolha a opção que voce quer realizar:\n");
    printf("1-criar cliente\n");
    printf("2-apagar cliente\n");
    printf("3-fazer debito\n");
    printf("4-fezer deposito \n");
    printf("5-ver extrato\n");
    printf("6-transferencia de conta\n");
    printf("7-lista cliente\n");
    printf("8-sair\n");
    printf("digite uma opcao: \n");
}
char *criar_path(char cpf[12]) {
    char *path; // Criando um path para poder procurar os clientes.
    sprintf(path, "%s/cliente", cpf);
    return path;
}

Cliente *procurarCliente(char cpf[12]) {
    char path[30];
    sprintf(path, "%s/cliente", cpf);
    Cliente *clientes = (Cliente *)malloc(sizeof(Cliente)); // Verificar se o cliente
    FILE *t = fopen(path, "rb"); // Abrir, ler se tem e logo em seguida fechar.
    if (t == NULL) // Fazendo a verificação do CPF
        return NULL;
    fread(clientes, sizeof(Cliente), 1, t);
    fclose(t);
    return clientes;
}

// Cfunção para atualizar o valor do cliente de acordo
// com as funções de débito, depósito e transferência.
void *attCliente(char cpf[12], Cliente *c) {
    char path_att[30];
    sprintf(path_att, "%s/cliente", cpf);
    FILE *a = fopen(path_att, "wb");
    fwrite(c, sizeof(Cliente), 1, a);
    fclose(a);
    return 0;
}

// função para criar um extrato assim que o cliente cria uma conta
// para facilitar a manipulação no futuro.
void *criarExt(char cpf_extrato[12]) {
    char path_ext[30];
    sprintf(path_ext, "%s/extrato.txt", cpf_extrato);
    FILE *ext = fopen(path_ext, "w");
    fclose(ext);
    return 0;
}

// função para adicionar um extrato dentro do arquivo extrato
// adicionando por linha.
void *adicionarExt(char e[100], char cpf_ext[12]) {
    char path_ext[30];
    sprintf(path_ext, "%s/extrato.txt", cpf_ext);
    FILE *extrato = fopen(path_ext, "a"); // Abrindo o arquivo e adicionando
    char add_ext[100];
    time_t data; // Pegando a data e o horário da operação
    time(&data);
    sprintf(add_ext, "%s%s\n", ctime(&data), e);
    fputs(add_ext, extrato); // Adiciono o add_ext no arquivo extrato
    fclose(extrato);
    return 0;
}

void clearBuffer() { // Para limpar o buffer
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
}

void criar_cliente() {
    clearBuffer();
    Cliente *clientes =
            (Cliente *)malloc(sizeof(Cliente)); // Cliente novo (ponteiro).
    printf("\n------------------------------\n"); // Informações do cliente.
    printf("Vamos criar uma conta para você!\n");
    printf("Preencha os dados a seguir\n\n");
    printf("Insira seu primeiro nome: ");
    fgets(clientes->nome, 100, stdin);

    printf("\nInsira seu CPF (somente 11 números): ");
    scanf("%s", clientes->cpf);

    printf("\nconta comum( 5%% de taxa a cada débito realizado)\n");
    printf("Você terá um saldo negativo de até RS 1.000,00\n");

    printf("\nconta plus( 3%% de taxa a cada débito realizado)\n");
    printf("Você terá um saldo negativo de até RS 5.000,00\n");
    printf("\ndigite 0 para conta comum e 1 para conta plus, qual vai desejar criar? ");
    scanf("%d", &clientes->tipo);

    // Se a tecla que o cliente digitou for diferente de 1 ou 0, vai dar erro
    if (clientes->tipo != 1 && clientes->tipo != 0) {
        printf("\nTipo de conta inválido! Tente novamente\n");
        return;
    }

    printf("\nDigite o valor inicial da sua conta: ");
    scanf("%lf", &clientes->valor_entrada);
    printf("\nDigite sua senha: ");
    scanf("%d", &clientes->senha);

    clearBuffer();
    // Avisando ao cliente sobre o cadastro.
    printf("\n------------------------------\n");
    printf("Cliente cadastrado!!\n");
    printf("Nome: %s", clientes->nome);
    printf("CPF: %s", clientes->cpf);
    printf("\nTipo da conta: ");
    if (clientes->tipo ==
        0) { // Fiz isso somente para printar contas comum ou plus.
        printf("Conta comum!\n");
    }
    if (clientes->tipo == 1) {
        printf("Conta plus!\n");
    }

    // Printando o valor do cliente
    printf("Valor inicial: %.2lf\n", clientes->valor_entrada);
    // Printando a data de nascimento dele
    printf("Data de nascimento: ");


    mkdir(clientes->cpf); // Criar uma pasta de CPF.
    char path_cpf[30]; // Criei para poder jogar o arquivo dentro da pasta.
    // Gerando o caminho para salvar os arquivos
    sprintf(path_cpf, "%s/cliente", clientes->cpf);

    // Estou abrindo o arquivo para colocar os valores lá dentro.
    FILE *f = fopen(path_cpf, "wb");
    fwrite(clientes, sizeof(Cliente), 1, f); // Colocando os valores....
    fclose(f); // Fechando o arquivo.

    criarExt(clientes->cpf); // Criando um arquivo extrato para cada cliente criado
    return;
    clearBuffer();
}