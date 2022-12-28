#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <signal.h>
#include <errno.h>
#include <pthread.h>
#include <sys/select.h>

#define TAM_LIST 4000
#define TAM_MAX 256
#define BACKEND_FIFO "../backend_files/BACKEND_FIFO" ///Users/joaocarvalho/Desktop/Universidade/2oAno/SO/TP/TP-SO/backend_files/BACKEND_FIFO
#define SINAL_FIFO  "../backend_files/SINAL_FIFO"
#define UTILIZADOR "../frontend_files/UTILIZADOR_%d" ///Users/joaocarvalho/Desktop/Universidade/2oAno/SO/TP/TP-SO/frontend_files/UTILIZADOR_%d

char UTILIZADOR_FIFO_FINAL[TAM_MAX];
//isto so vai ser acedido e incrementado no backend, no frontend apenas e criado um cliente e no backend é que os meto em posicoes diferentes

//Estruturas Gerais

typedef struct Clientes{
    pid_t pid;
    char nome[TAM_MAX];
    char password[TAM_MAX];
    char comando[TAM_MAX];
    int saldo;
    int hBeat;
    int is_logged_in;
    pthread_mutex_t m;
    int tempo_log;
} Clientes;

typedef struct Promotor{
    char message[TAM_MAX];
    char categoria[TAM_MAX];
    int desconto;
    int duracao;
} Promotor;

typedef struct Itens
{
    int id;
    char nome[TAM_MAX];
    char categoria[TAM_MAX];
    int preco_base; //valor a ser incrementado
    int comprar_ja;
    int tempo;
    char nomeV[TAM_MAX];
    char nomeC[TAM_MAX];
} Itens;

typedef struct ambientVars{
    char* FPROMOTERS;
    char* FUSERS;
    char* FITEMS;
    int HEARTBEAT;
}ambientVars;

typedef struct Backend{
    Clientes* clientes;
    Itens* itens;
    ambientVars* aVars;
    char msg[100];
    int tempo_run;
}Backend;

typedef struct {
    pid_t pid;
    int hBeat;
    //int clienteSaldo;
    char msg[TAM_LIST];
}dataMSG;