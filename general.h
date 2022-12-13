#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <signal.h>
#include <errno.h>

#define TAM 50
#define BACKEND_FIFO "BACKEND_FIFO"
#define UTILIZADOR "UTILIZADOR%d"

//Estruturas Gerais

typedef struct Clientes{
    pid_t pid;
    char nome[TAM];
    char password[TAM];
    int saldo;
} Clientes, *ptrClientes;

typedef struct Promotor{
    char message[TAM];
    char categoria[TAM];
    int desconto;
    int duracao;
} Promotor, *ptrPromotor;

typedef struct Itens
{
    int id;
    char nome[TAM];
    char categoria[TAM];
    int preco_base; //valor a ser incrementado
    int comprar_ja;
    int tempo;
    char nomeV[TAM];
    char nomeC[TAM];
} Itens, *ptrItens;

typedef struct ambientVars{
    char* FPROMOTERS;
    char* FUSERS;
    char* FITEMS;
}ambientVars, *ptrAmbientVars;

typedef struct Backend{
    ptrClientes clientes;
    ptrItens itens;
    ptrAmbientVars aVars;
}Backend, *ptrBackend;