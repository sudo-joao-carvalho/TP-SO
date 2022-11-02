#include "frontend.h"

int main(int argc, char** argv){

    char* user = argv[1];
    char* pass = argv[2];
    ptrClientes client = malloc(sizeof(Clientes));

    if(argc < 3){
        printf("[ERRO] Numero de comandos inseridos invalido\n");
        printf("[FORMATO] ./frontend username password");
        return -1;
    }else if(argc > 3){
        printf("[ERRO] Numero de comandos inseridos invalido\n");
        printf("[FORMATO] ./frontend username password");
        return -1;
    }

    if(argc == 3){
        strcpy(client->nome, user);
        strcpy(client->password, pass);

        //printf("%s %s", client->nome, client->password); 
    }

    return 0;

}