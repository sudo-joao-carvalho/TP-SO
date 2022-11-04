#include "frontend.h"

bool lerCommands(){

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

int main(int argc, char** argv){

    char* user = argv[1];
    char* pass = argv[2];
    char initCommand[TAM];
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

        printf("Deseja testar que funcionalidade? <comandos> || <execuçao promotor> || <utilizador> || <itens> \n");
        scanf(" %s", initCommand);

        if(strcmp(initCommand, "comandos") == 0){
            if(lerCommands() == false) return 0;
        }else if(strcmp(initCommand, "execucao") == 0){

            int fid = fork();

            if(fid < 0){
                printf("[ERRO] Backend nao foi criado com sucesso\n");
                return -4;
            }else if(fid == 0){
                execl("/Users/joaocarvalho/Desktop/Universidade/2oAno/SO/TP/TP-SO/backend_files/backend", "./backend", NULL);
            }else if(fid > 0){
                wait(&fid);
            }
            
        }else if(strcmp(initCommand, "utilizador") == 0){
            printf("\nutilizador\n");
        }else if(strcmp(initCommand, "itens") == 0){
            printf("\nitens\n");
        }else{
            printf("\n\t[ERRO] Comando errado");
            return -1;
        }

        //while(1)
        //    if(lerCommands() == false) return 0;

    }

    return 0;

}