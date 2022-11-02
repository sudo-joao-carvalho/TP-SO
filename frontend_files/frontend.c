#include "frontend.h"

int main(int argc, char* argv){

    char* user = argv[1];
    char* pass = argv[2];
    ptrClientes client = malloc(sizeof(Clientes));

    if(argc < 3){
        printf("[ERRO] Numero de comandos inseridos invalido");
        return -1;
    }

    if(argc == 3){
        client->nome = user;
        client->password = pass; 
    }

    return 0;

}