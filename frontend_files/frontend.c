#include "frontend.h"

int main(int argc, char** argv){

    char* user = argv[1];
    char* pass = argv[2];
    char* aux;
    char** command = malloc(5 * sizeof(char*));
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
        int i = 0;

        printf("Insira o comando que pretende executar: ");
        do{
            scanf(" %s", aux);
            strcpy(command[i], aux);
            i++;
        }while(strcmp(command[i], "\n") != 0);

        if(strcmp(command[0], "sell") == 0){
        
        }/*else if(strcmp(command[0], "list") == 0){

        }else if(strcmp(command[0], "licat") == 0){
            
        }else if(strcmp(command[0], "lisel") == 0){
            
        }else if(strcmp(command[0], "lival") == 0){
            
        }else if(strcmp(command[0], "litime") == 0){
            
        }else if(strcmp(command[0], "time") == 0){
            
        }else if(strcmp(command[0], "buy") == 0){
            
        }else if(strcmp(command[0], "cash") == 0){
            
        }else if(strcmp(command[0], "add") == 0){
            
        }else if(strcmp(command[0], "exit") == 0){
            
        }*/else{
            printf("[ERRO] Comando invalido");
            return -1;
        }
    }

    

    /*switch(*command){
        case 'sell':
        case 'list':
        case 'licat':
        case 'lisel':
        case 'lival':
        case 'litime':
        case 'time':
        case 'buy':
        case 'cash':
        case 'add':
        case 'exit':
        
        default:
    }*/

    return 0;

}