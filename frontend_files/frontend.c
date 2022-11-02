#include "frontend.h"

bool lerCommands(){

    char command[TAM];
    char firstCommand[10];
    char* token;

    printf("Insira o comando que pretende executar: ");
    fgets(command, TAM, stdin);

    token = strtok(command, " \n");

    int spaceCounts = 0;
    while(token != NULL){
        if(spaceCounts == 0){
            strcpy(firstCommand, token);
        }
        spaceCounts++;

        printf("%d\n", spaceCounts);
        token = strtok(NULL, " ");
    }

    if(strcmp(firstCommand, "sell") == 0){

        if(spaceCounts == 6){
            printf("Numero de argumentos valido\n");
            printf("COMANDO SELL EM EXECUCAO");
        }else if(spaceCounts < 6){
            printf("[ERRO] Numero de argumentos invalido\n");
            printf("[FORMATO] sell <nome-item> <categoria> <preço-base> <preço-compre-já> <duração>");
        }else if(spaceCounts > 6){
            printf("[ERRO] Numero de argumentos invalido\n");
            printf("[FORMATO] sell <nome-item> <categoria> <preço-base> <preço-compre-já> <duração>");
        }

        return true;

    }else if(strcmp(firstCommand, "list") == 0){

        if(spaceCounts == 1){
            printf("Numero de argumentos valido\n");
            printf("COMANDO LIST EM EXECUCAO");
        }else if(spaceCounts < 1){
            printf("[ERRO] Numero de argumentos invalido\n");
            printf("[FORMATO] list");
        }else if(spaceCounts > 1){
            printf("[ERRO] Numero de argumentos invalido\n");
            printf("[FORMATO] list");
        }

        return true;

    }else if(strcmp(firstCommand, "licat") == 0){

        if(spaceCounts == 2){
            printf("Numero de argumentos valido\n");
            printf("COMANDO LICAT EM EXECUCAO");
        }else if(spaceCounts < 2){
            printf("[ERRO] Numero de argumentos invalido\n");
            printf("[FORMATO] licat <nome-categoria");
        }else if(spaceCounts > 2){
            printf("[ERRO] Numero de argumentos invalido\n");
            printf("[FORMATO] licat <nome-categoria");
        }

        return true;

    }else if(strcmp(firstCommand, "lisel") == 0){
            
        if(spaceCounts == 2){
            printf("Numero de argumentos valido\n");
            printf("COMANDO LISEL EM EXECUCAO");
        }else if(spaceCounts < 2){
            printf("[ERRO] Numero de argumentos invalido\n");
            printf("[FORMATO] lisel <username do vendedor>");
        }else if(spaceCounts > 2){
            printf("[ERRO] Numero de argumentos invalido\n");
            printf("[FORMATO] lisel <username do vendedor>");
        }

        return true;

    }else if(strcmp(firstCommand, "lival") == 0){
            
        if(spaceCounts == 2){
            printf("Numero de argumentos valido\n");
            printf("COMANDO LIVAL EM EXECUCAO");
        }else if(spaceCounts < 2){
            printf("[ERRO] Numero de argumentos invalido\n");
            printf("[FORMATO] lival <preço-máximo>");
        }else if(spaceCounts > 2){
            printf("[ERRO] Numero de argumentos invalido\n");
            printf("[FORMATO] lival <preço-máximo>");
        }

        return true;

    }else if(strcmp(firstCommand, "litime") == 0){
            
        if(spaceCounts == 2){
            printf("Numero de argumentos valido\n");
            printf("COMANDO LITIME EM EXECUCAO");
        }else if(spaceCounts < 2){
            printf("[ERRO] Numero de argumentos invalido\n");
            printf("[FORMATO] litime <hora-em-segundos>");
        }else if(spaceCounts > 2){
            printf("[ERRO] Numero de argumentos invalido\n");
            printf("[FORMATO] litime <hora-em-segundos>");
        }
          
        return true;

    }else if(strcmp(firstCommand, "time") == 0){
            
        if(spaceCounts == 1){
            printf("Numero de argumentos valido\n");
            printf("COMANDO TIME EM EXECUCAO");
        }else if(spaceCounts < 1){
            printf("[ERRO] Numero de argumentos invalido\n");
            printf("[FORMATO] time");
        }else if(spaceCounts > 1){
            printf("[ERRO] Numero de argumentos invalido\n");
            printf("[FORMATO] time");
        }

        return true;

    }else if(strcmp(firstCommand, "buy") == 0){
        
        if(spaceCounts == 3){
            printf("Numero de argumentos valido\n");
            printf("COMANDO BUY EM EXECUCAO");
        }else if(spaceCounts < 3){
            printf("[ERRO] Numero de argumentos invalido\n");
            printf("[FORMATO] buy <id> <valor>");
        }else if(spaceCounts > 3){
            printf("[ERRO] Numero de argumentos invalido\n");
            printf("[FORMATO] buy <id> <valor>");
        }

        return true;

    }else if(strcmp(firstCommand, "cash") == 0){

        if(spaceCounts == 1){
            printf("Numero de argumentos valido\n");
            printf("COMANDO CASH EM EXECUCAO");
        }else if(spaceCounts < 1){
            printf("[ERRO] Numero de argumentos invalido\n");
            printf("[FORMATO] cash");
        }else if(spaceCounts > 1){
            printf("[ERRO] Numero de argumentos invalido\n");
            printf("[FORMATO] cash");
        }

        return true;

    }else if(strcmp(firstCommand, "add") == 0){
            
        if(spaceCounts == 2){
            printf("Numero de argumentos valido\n");
            printf("COMANDO ADD EM EXECUCAO");
        }else if(spaceCounts < 2){
            printf("[ERRO] Numero de argumentos invalido\n");
            printf("[FORMATO] add <valor>");
        }else if(spaceCounts > 2){
            printf("[ERRO] Numero de argumentos invalido\n");
            printf("[FORMATO] add <valor>");
        }

        return true;

    }else if(strcmp(firstCommand, "exit") == 0){

        if(spaceCounts == 1){
            printf("Numero de argumentos valido\n");
            printf("COMANDO EXIT EM EXECUCAO");
        }else if(spaceCounts < 2){
            printf("[ERRO] Numero de argumentos invalido\n");
            printf("[FORMATO] exit");
        }else if(spaceCounts > 2){
            printf("[ERRO] Numero de argumentos invalido\n");
            printf("[FORMATO] exit");
        }

        return false;
            
    }else{
        printf("[ERRO] Comando invalido");
        return true;
    }

}

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
        while(1){
            if(lerCommands() == false) return 0;
        }
        
    }

    return 0;

}