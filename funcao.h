#include "struct.h"

// nomeando todas as funcoes
void menu();
void criar_cliente();
void apagar_cliente();
void listarClientes();
void debito();
void deposito();
char *criar_path(char cpf[12]);
Cliente *procurarCliente(char cpf[12]);
void clearBuffer();
void *attCliente(char cpf[30], Cliente *clientes);
