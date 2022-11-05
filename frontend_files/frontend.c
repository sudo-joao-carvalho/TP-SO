#include "frontend.h"

void commandHelp(){

    printf("\n\n******************  Commands List  ******************\n\n");
    printf("--> sell <nome-item> <categoria> <preço-base> <preço-compre-já> <duração>\n");
    printf("--> list\n");
    printf("--> licat <nome-categoria\n");
    printf("--> lisel <username do vendedor>\n");
    printf("--> lival <preço-máximo>\n");
    printf("--> litime <hora-em-segundos>\n");
    printf("--> time\n");
    printf("--> buy\n");
    printf("--> cash\n");
    printf("--> add\n");
    printf("--> help\n");
    printf("--> exit\n");

}

bool readCommands(){

    char command[TAM];
    char firstCommand[10];
    char* token;

    fflush(stdin);

    printf("Insira o comando que pretende executar: ");
    fgets(command, TAM, stdin);

    token = strtok(command, " \n");

    int wordCounts = 0;
    while(token != NULL){
        if(wordCounts == 0){
            strcpy(firstCommand, token);
        }
        wordCounts++;

        token = strtok(NULL, " ");
    }

    if(strcmp(firstCommand, "sell") == 0){

        if(wordCounts == 6){
            printf("Numero de argumentos valido\n");
            printf("COMANDO SELL EM EXECUCAO\n");
        }else if(wordCounts < 6){
            printf("[ERRO] Numero de argumentos invalido\n");
            printf("[FORMATO] sell <nome-item> <categoria> <preço-base> <preço-compre-já> <duração>\n");
        }else if(wordCounts > 6){
            printf("[ERRO] Numero de argumentos invalido\n");
            printf("[FORMATO] sell <nome-item> <categoria> <preço-base> <preço-compre-já> <duração>\n");
        }

        return true;

    }else if(strcmp(firstCommand, "list") == 0){

        if(wordCounts == 1){
            printf("Numero de argumentos valido\n");
            printf("COMANDO LIST EM EXECUCAO\n");
        }else if(wordCounts < 1){
            printf("[ERRO] Numero de argumentos invalido\n");
            printf("[FORMATO] list\n");
        }else if(wordCounts > 1){
            printf("[ERRO] Numero de argumentos invalido\n");
            printf("[FORMATO] list\n");
        }

        return true;

    }else if(strcmp(firstCommand, "licat") == 0){

        if(wordCounts == 2){
            printf("Numero de argumentos valido\n");
            printf("COMANDO LICAT EM EXECUCAO\n");
        }else if(wordCounts < 2){
            printf("[ERRO] Numero de argumentos invalido\n");
            printf("[FORMATO] licat <nome-categoria\n");
        }else if(wordCounts > 2){
            printf("[ERRO] Numero de argumentos invalido\n");
            printf("[FORMATO] licat <nome-categoria\n");
        }

        return true;

    }else if(strcmp(firstCommand, "lisel") == 0){
            
        if(wordCounts == 2){
            printf("Numero de argumentos valido\n");
            printf("COMANDO LISEL EM EXECUCAO\n");
        }else if(wordCounts < 2){
            printf("[ERRO] Numero de argumentos invalido\n");
            printf("[FORMATO] lisel <username do vendedor>\n");
        }else if(wordCounts > 2){
            printf("[ERRO] Numero de argumentos invalido\n");
            printf("[FORMATO] lisel <username do vendedor>\n");
        }

        return true;

    }else if(strcmp(firstCommand, "lival") == 0){
            
        if(wordCounts == 2){
            printf("Numero de argumentos valido\n");
            printf("COMANDO LIVAL EM EXECUCAO\n");
        }else if(wordCounts < 2){
            printf("[ERRO] Numero de argumentos invalido\n");
            printf("[FORMATO] lival <preço-máximo>\n");
        }else if(wordCounts > 2){
            printf("[ERRO] Numero de argumentos invalido\n");
            printf("[FORMATO] lival <preço-máximo>\n");
        }

        return true;

    }else if(strcmp(firstCommand, "litime") == 0){
            
        if(wordCounts == 2){
            printf("Numero de argumentos valido\n");
            printf("COMANDO LITIME EM EXECUCAO\n");
        }else if(wordCounts < 2){
            printf("[ERRO] Numero de argumentos invalido\n");
            printf("[FORMATO] litime <hora-em-segundos>\n");
        }else if(wordCounts > 2){
            printf("[ERRO] Numero de argumentos invalido\n");
            printf("[FORMATO] litime <hora-em-segundos>\n");
        }
          
        return true;

    }else if(strcmp(firstCommand, "time") == 0){
            
        if(wordCounts == 1){
            printf("Numero de argumentos valido\n");
            printf("COMANDO TIME EM EXECUCAO\n");
        }else if(wordCounts < 1){
            printf("[ERRO] Numero de argumentos invalido\n");
            printf("[FORMATO] time\n");
        }else if(wordCounts > 1){
            printf("[ERRO] Numero de argumentos invalido\n");
            printf("[FORMATO] time\n");
        }

        return true;

    }else if(strcmp(firstCommand, "buy") == 0){
        
        if(wordCounts == 3){
            printf("Numero de argumentos valido\n");
            printf("COMANDO BUY EM EXECUCAO\n");
        }else if(wordCounts < 3){
            printf("[ERRO] Numero de argumentos invalido\n");
            printf("[FORMATO] buy <id> <valor>\n");
        }else if(wordCounts > 3){
            printf("[ERRO] Numero de argumentos invalido\n");
            printf("[FORMATO] buy <id> <valor>\n");
        }

        return true;

    }else if(strcmp(firstCommand, "cash") == 0){

        if(wordCounts == 1){
            printf("Numero de argumentos valido\n");
            printf("COMANDO CASH EM EXECUCAO\n");
        }else if(wordCounts < 1){
            printf("[ERRO] Numero de argumentos invalido\n");
            printf("[FORMATO] cash\n");
        }else if(wordCounts > 1){
            printf("[ERRO] Numero de argumentos invalido\n");
            printf("[FORMATO] cash\n");
        }

        return true;

    }else if(strcmp(firstCommand, "add") == 0){
            
        if(wordCounts == 2){
            printf("Numero de argumentos valido\n");
            printf("COMANDO ADD EM EXECUCAO\n");
        }else if(wordCounts < 2){
            printf("[ERRO] Numero de argumentos invalido\n");
            printf("[FORMATO] add <valor>\n");
        }else if(wordCounts > 2){
            printf("[ERRO] Numero de argumentos invalido\n");
            printf("[FORMATO] add <valor>\n");
        }

        return true;

    }else if(strcmp(firstCommand, "help") == 0){

        if(wordCounts == 1){
            printf("Numero de argumentos valido\n");
            commandHelp();
        }else if(wordCounts < 2){
            printf("[ERRO] Numero de argumentos invalido\n");
            printf("[FORMATO] help\n");
        }else if(wordCounts > 2){
            printf("[ERRO] Numero de argumentos invalido\n");
            printf("[FORMATO] help\n");
        }

        return false;

    }else if(strcmp(firstCommand, "exit") == 0){

        if(wordCounts == 1){
            printf("Numero de argumentos valido\n");
            printf("COMANDO EXIT EM EXECUCAO\n");
        }else if(wordCounts < 2){
            printf("[ERRO] Numero de argumentos invalido\n");
            printf("[FORMATO] exit\n");
        }else if(wordCounts > 2){
            printf("[ERRO] Numero de argumentos invalido\n");
            printf("[FORMATO] exit\n");
        }

        return false;
            
    }else{
        printf("[ERRO] Comando invalido\n\n");
        return true;
    }

}

/*int main(int argc, char** argv){

    char* user = argv[1];
    char* pass = argv[2];
    ptrClientes client = malloc(sizeof(Clientes));

    if(argc < 3){
        printf("[ERRO] Numero de comandos inseridos invalido\n");
        printf("[FORMATO] ./frontend username password\n");
        return -1;
    }else if(argc > 3){
        printf("[ERRO] Numero de comandos inseridos invalido\n");
        printf("[FORMATO] ./frontend username password\n");
        return -1;
    }

    if(argc == 3){

        strcpy(client->nome, user);
        strcpy(client->password, pass);
        //while(1)
        //    if(lerCommands() == false) return 0;

    }

    return 0;

}*/