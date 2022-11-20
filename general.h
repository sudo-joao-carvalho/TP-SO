#include <signal.h>
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