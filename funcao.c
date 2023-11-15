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

void apagar_cliente() {
    // Declaração de variável para armazenar o CPF a ser apagado
    char cpf_apagar[12];

    // Mensagens de interação com o usuário
    printf("Exclusão de Conta\n");
    printf("Por favor, preencha os dados a seguir:\n");
    printf("Digite o CPF da conta que você deseja apagar: ");
    scanf("%s", cpf_apagar);

    // Busca do cliente pelo CPF inserido
    Cliente *cliente = procurarCliente(cpf_apagar);

    // Verificação se o cliente foi encontrado
    if (cliente == NULL) {
        printf("\nCPF não encontrado, conta inexistente!\n");
        return;
    }

    // Construção do caminho do diretório a ser removido
    char path_apagar[30];
    sprintf(path_apagar, "%s/cliente", cpf_apagar);
    remove(path_apagar);

    // Remoção do arquivo de extrato
    sprintf(path_apagar, "%s/extrato.txt", cpf_apagar);
    remove(path_apagar);

    // Remoção do diretório do cliente
    rmdir(cpf_apagar);

    // Mensagens de conclusão
    printf("\nCONTA REMOVIDA COM SUCESSO!\n");
    printf("Até logo...\n");

    // Limpeza do buffer do teclado
    clearBuffer();
}


void listarClientes() {
    struct dirent *ent;
    DIR *dir = opendir("."); // Abre o diretório atual

    if (dir == NULL) {
        perror("Erro ao abrir o diretório.");
        return;
    }
// o while para mostrar todas as contas existentes
    while ((ent = readdir(dir)) != NULL) {
        if (strlen(ent->d_name) == 11) {
            char path_cpf[30];
            sprintf(path_cpf, "%s/cliente", ent->d_name);

            FILE *f = fopen(path_cpf, "rb");
            if (f != NULL) {
                Cliente cliente;
                fread(&cliente, sizeof(Cliente), 1, f);
                fclose(f);

                printf("Nome: %s\n", cliente.nome);
                printf("CPF: %s\n", cliente.cpf);
                printf("Tipo da conta: %s\n", (cliente.tipo == 0) ? "Conta comum" : "Conta plus");
                printf("Valor inicial: %.2lf\n", cliente.valor_entrada);
                printf("------------------------------\n");
            }
        }
    }

    closedir(dir);
}

// Função para realizar débito na conta do cliente
void debito() {
    // Mensagens de interação com o usuário
    printf("Vamos fazer um débito!\n");
    printf("Preencha os dados a seguir\n");

    // Declaração de variáveis para armazenar dados inseridos pelo usuário
    char cpf_debito[12];
    printf("Digite o CPF correspondente à conta que deseja fazer um débito: ");
    scanf("%s", cpf_debito);

    // Busca do cliente pelo CPF inserido
    Cliente *cliente = procurarCliente(cpf_debito);

    // Verificação se o cliente foi encontrado
    if (cliente == NULL) {
        printf("\nCPF inválido, tente novamente!\n");
        return;
    }

    // Verificação da senha
    int senha;
    printf("Digite sua senha: ");
    scanf("%d", &senha);

    if (senha != cliente->senha) {
        printf("\nSenha incorreta, tente novamente!\n");
        return;
    }

    // Cálculo da taxa com base no tipo de cliente
    double valor_debito;
    printf("Valor que deseja retirar: ");
    scanf("%lf", &valor_debito);

    float taxa;
    if (cliente->tipo == 0) {
        taxa = valor_debito * 0.05;
    } else if (cliente->tipo == 1) {
        taxa = valor_debito * 0.03;
    }

    // Cálculo do valor final após a taxa
    double valor_taxado = valor_debito + taxa;
    double novo_valor = cliente->valor_entrada - valor_taxado;

    // Verificação de limite
    if ((novo_valor < -1000 && cliente->tipo == 0) ||
        (novo_valor < -5000 && cliente->tipo == 1)) {
        printf("Ultrapassou o limite, tente novamente!\n");
        return;
    }

    // Atualização dos dados do cliente
    cliente->valor_entrada = novo_valor;

    // Registro da operação no extrato da conta
    char debito[100];
    sprintf(debito, "Débito: RS%.2lf; Taxa: RS%.2lf; Valor atual: %.2lf", valor_debito, taxa, cliente->valor_entrada);
    adicionarExt(debito, cpf_debito);
    attCliente(cpf_debito, cliente);

    // Mensagens de conclusão
    printf("O débito foi realizado\n");
    printf("Opção 5 para visualizar o extrato\n");
    printf("Até logo...\n");

    // Limpeza do buffer do teclado
    clearBuffer();
}

void deposito() {
    // Declaração de variáveis para armazenar dados inseridos pelo usuário
    char cpf_deposito[12];
    int senha_deposito;

    // Mensagens de interação com o usuário
    printf("\n------------------------------\n");
    printf("Depósito Bancário\n");
    printf("Por favor, preencha os dados a seguir\n");

    // Solicitação do CPF e busca do cliente
    printf("Digite o CPF da conta em que deseja fazer um depósito: ");
    scanf("%s", cpf_deposito);

    Cliente *cliente = procurarCliente(cpf_deposito);

    // Verificação se o cliente foi encontrado
    if (cliente == NULL) {
        printf("\nCPF não encontrado, por favor, tente novamente!\n");
        return;
    }

    // Verificação da senha
    printf("Digite sua senha: ");
    scanf("%d", &senha_deposito);

    if (senha_deposito != cliente->senha) {
        printf("\nSenha incorreta, por favor, tente novamente!\n");
        return;
    }

    // Solicitação do valor do depósito e atualização do saldo
    double valor_deposito;
    printf("Digite o valor que deseja depositar: ");
    scanf("%lf", &valor_deposito);

    double novo_valor = cliente->valor_entrada + valor_deposito;
    cliente->valor_entrada = novo_valor;

    // Registro da operação no extrato da conta
    char deposito[100];
    sprintf(deposito, "Depósito: RS%.2lf; Saldo atual: %.2lf", valor_deposito, cliente->valor_entrada);
    adicionarExt(deposito, cpf_deposito);
    attCliente(cpf_deposito, cliente);

    // Mensagens de conclusão
    printf("Depósito realizado com sucesso!\n");
    printf("Para visualizar seu extrato, digite 5!\n");
    printf("Até logo!\n");

    // Limpeza do buffer do teclado
    clearBuffer();
}