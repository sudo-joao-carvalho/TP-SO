#include <stdio.h>

#define TAM 50

//Estruturas Gerais

typedef struct Clientes{
    char nome[TAM];
    char password[TAM];
    int saldo;
} Clientes, *ptrClientes;