#include "struct.h"

// nomeando todas as funcoes
void menu();
void criar_cliente();
void apagar_cliente();
void debito();
void deposito();
void extrato();
void transferencia();
void listarClientes();
char *criar_path(char cpf[12]);
Cliente *procurarCliente(char cpf[12]);
void clearBuffer();
void *attCliente(char cpf[30], Cliente *clientes);
void *criarExt(char cpf_extrato[30]);
void *adicionarExt(char e[100], char cpf_ext[30]);