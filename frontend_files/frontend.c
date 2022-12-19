#include "frontend.h"
#include "../general.h"

/* void sig_handler_heartbeat(int s, siginfo_t *i, void *v){
    printf("Continuo Logged In");
} */

void commandHelp(){

    printf("\n\n******************  Commands List  ******************\n\n");
    printf("--> sell <nome-item> <categoria> <preço-base> <preço-compre-já> <duração>\n");
    printf("--> list\n");
    printf("--> licat <nome-categoria>\n");
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

char* readCommands(char* CommandM){

    char command[TAM_MAX];
    char firstCommand[10];
    char* token;

    fflush(stdin);

    printf("Insira o comando que pretende executar: ");
    fgets(command, TAM_MAX, stdin);

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

        CommandM = firstCommand;

        return CommandM;

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

        CommandM = firstCommand;

        return CommandM;

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

        CommandM = firstCommand;

        return CommandM;

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

        CommandM = firstCommand;

        return CommandM;

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

        CommandM = firstCommand;

        return CommandM;

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
          
        CommandM = firstCommand;

        return CommandM;

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

        CommandM = firstCommand;

        return CommandM;

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

        CommandM = firstCommand;

        return CommandM;

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

        CommandM = firstCommand;

        return CommandM;

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

        CommandM = firstCommand;

        return CommandM;

    }else if(strcmp(firstCommand, "help") == 0){

        if(wordCounts == 1){
            printf("Numero de argumentos valido\n");
            commandHelp();
        }else if(wordCounts < 1){
            printf("[ERRO] Numero de argumentos invalido\n");
            printf("[FORMATO] help\n");
        }else if(wordCounts > 1){
            printf("[ERRO] Numero de argumentos invalido\n");
            printf("[FORMATO] help\n");
        }

        CommandM = firstCommand;

        return CommandM;

    }else if(strcmp(firstCommand, "exit") == 0){

        if(wordCounts == 1){
            printf("Numero de argumentos valido\n");
            printf("COMANDO EXIT EM EXECUCAO\n");
        }else if(wordCounts < 1){
            printf("[ERRO] Numero de argumentos invalido\n");
            printf("[FORMATO] exit\n");
        }else if(wordCounts > 1){
            printf("[ERRO] Numero de argumentos invalido\n");
            printf("[FORMATO] exit\n");
        }

        CommandM = firstCommand;

        return CommandM;
            
    }else{
        printf("[ERRO] Comando invalido\n\n");
        return "Comando Invalido";
    }

}

void* enviaHEARTBEATorMSG(void* msgHeartBeat){

    Backend* pMsgHeartBeat = (Backend*) msgHeartBeat;

    pthread_mutex_lock(&pMsgHeartBeat->clientes->m);
        int size = write(pMsgHeartBeat->clientes->fd, &pMsgHeartBeat->clientes, sizeof(pMsgHeartBeat->clientes)); //envia o username
        if(size <= 0){
            perror("\n[ERRO] Erro no envio da mensagem HEARTBEAT\n");
        }
    pthread_mutex_unlock(&pMsgHeartBeat->clientes->m);
    //close(pMsgHeartBeat->clientes->fd);

    pthread_exit(NULL);

}

int main(int argc, char** argv){

    char* user = argv[1];
    char* pass = argv[2];
    char* command;
    char msg[TAM_MAX];
    Backend backend;
    backend.clientes = malloc(sizeof(backend.clientes));
    backend.aVars = malloc(sizeof(backend.aVars));
    //backend.clientes->m = malloc(sizeof(backend.clientes->m));
    int nfd;
    fd_set read_fds;
    struct timeval tv;
    pthread_t thread[2];
    pthread_mutex_init(&backend.clientes->m, NULL);
    dataMSG msgFromBackend;
    int backend_fd;

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

        strcpy(backend.clientes->nome, user);
        strcpy(backend.clientes->password, pass);
        strcpy(backend.clientes->msgHB, "Continuo Loggado  --> User: ");
        strcat(backend.clientes->msgHB, backend.clientes->nome);

        //ENVIO DAS CREDENCIAIS PARA O BACKEND
        sprintf(UTILIZADOR_FIFO_FINAL, UTILIZADOR, getpid());

        if(access(UTILIZADOR_FIFO_FINAL, F_OK) == 0) {
            printf("\n[ERRO] Esse utilizador ja existe\n");
            exit(0);
        }

        mkfifo(UTILIZADOR_FIFO_FINAL, 0666);

        int utilizador_fd = open(UTILIZADOR_FIFO_FINAL, O_RDWR); //receber a msg de login
        if (utilizador_fd == -1){
            printf("Erro ao abrir utilizador");
            return -1;
        }

        backend_fd = open(BACKEND_FIFO, O_RDWR); //enviar as credenciais
        if (backend_fd == -1){
            printf("Erro o servidor não está a correr");
            unlink(UTILIZADOR_FIFO_FINAL);
            return -1;
        }

        backend.clientes[0].pid = getpid();
        backend.clientes->fd = backend_fd;
        printf("nome: %s\n", backend.clientes->nome);
        printf("password: %s\n", backend.clientes->password);
        printf("pid: %d\n", backend.clientes->pid);
        printf("backend_fd: %d\n", backend_fd);
        printf("fd: %d\n", backend.clientes->fd);
        
        int size = write(backend_fd, &(backend.clientes[0]), sizeof(backend.clientes[0])); //envia as credenciais
        if(size <= 0){
            printf("\n[ERRO] Erro no envio do username e da password\n");
        }

        while(strcmp(command, "exit") != 0){

            tv.tv_sec = 5;
            tv.tv_usec = 0;

            FD_ZERO(&read_fds);
            FD_SET(0, &read_fds);
            FD_SET(utilizador_fd, &read_fds);

            nfd = select(utilizador_fd + 1, &read_fds, NULL, NULL, &tv);

            if(nfd == -1){
                printf("\nNada a receber\n");
                exit(0);
            }
            
            if(nfd == 0){
                printf("\n Estou a espera de comandos ou de mensagem do backend\n");
            }

            //ENVIO DAS CREDENCIAIS PARA O BACKEND

            if(FD_ISSET(0, &read_fds)){ 
                //Aqui esta a escuta de comandos do utilizador
                scanf(" %s", command);
            }else if(FD_ISSET(utilizador_fd, &read_fds)){
                //Aqui esta a escuta que algo seja escrito no pipe utilizador_fd
                
                //RECEBE MENSAGEM A CONFIRMAR QUE FOI LOGADO
                int size2 = read(utilizador_fd, &msgFromBackend, sizeof(msgFromBackend));
                if(size2 < 0){
                    perror("Erro ao ler no pipe\n");
                }

                //ASSIGN HEARTBEAT VARIABLES
                backend.aVars->HEARTBEAT = msgFromBackend.hBeat;
                backend.clientes->hBeat = msgFromBackend.hBeat;
                printf("heartbeat: %d\n", backend.clientes->hBeat);

                if(strcmp(msgFromBackend.msg, "Usuario Valido\n") == 0)
                    printf("Login feito com sucesso\n");
                else if(strcmp(msgFromBackend.msg, "[ERRO] Utilizador nao existe/password invalida\n") == 0){
                    printf("Login invalido\n");
                    kill(getpid(), SIGTERM);
                }else if(strcmp(msgFromBackend.msg, "\n[ERRO] Usuario ja esta loggado\n") == 0){
                    printf("Usuario ja se encontra loggado\n");
                    kill(getpid(), SIGTERM);
                }
                
            }

            if(pthread_create(&thread[0], NULL, &enviaHEARTBEATorMSG, &backend.clientes) != 0)
                    return -1;
            sleep(backend.aVars->HEARTBEAT);
                

        }
        pthread_join(thread[0], NULL);
        pthread_mutex_destroy(&backend.clientes->m);
            
    }
    close(backend_fd);
    free(backend.clientes); //FAZER ISTO QUANDO O CLIENTE DER LOGOUT
    return 0;

}