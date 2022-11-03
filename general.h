#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>

#define TAM 50

//Estruturas Gerais

typedef struct Clientes{
    char nome[TAM];
    char password[TAM];
    int saldo;
} Clientes, *ptrClientes;

/*typedef struct Promotor{

}*/