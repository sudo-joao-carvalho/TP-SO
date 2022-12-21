#include "frontend.h"
#include "../general.h"

/* void sig_handler_heartbeat(int s, siginfo_t *i, void *v){
    printf("Continuo Logged In");
} */

int backend_fd;
int utilizador_fd;
int sinal_fd;

void sigterm_handler(){
    printf("Login invalido");
    unlink(UTILIZADOR_FIFO_FINAL);
    exit(EXIT_FAILURE);
}


int max(int a, int b){
    return (a > b) ? a : b;
}

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

    Clientes* pMsgHeartBeat = (Clientes*) msgHeartBeat;
    int aux = pMsgHeartBeat->pid;

    while(1){
        sleep(pMsgHeartBeat->hBeat);
        //pthread_mutex_lock(&pMsgHeartBeat->m);
            sinal_fd = open(SINAL_FIFO, O_RDWR | O_NONBLOCK);
            int ola = write(sinal_fd, &aux, sizeof(aux));
            if(ola <= 0){
                perror("\n[ERRO] Erro no envio da mensagem HEARTBEAT\n");
            }
        //pthread_mutex_unlock(&pMsgHeartBeat->m);
        close(sinal_fd);
        //close(backend_fd);
    }

    //pthread_exit(NULL);

}

int main(int argc, char** argv){

    char* user = argv[1];
    char* pass = argv[2];
    char* command;
    char msg[TAM_MAX];
    Clientes cliente;
    int nfd;
    fd_set read_fds;
    struct timeval tv;
    pthread_t thread;
    //pthread_mutex_init(&cliente.m, NULL);
    dataMSG msgFromBackend;
    cliente.tempo_log = 0;
    cliente.is_logged_in = 0;

    signal(SIGTERM, sigterm_handler);
    cliente.pid = getpid();

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

        strcpy(cliente.nome, user);
        strcpy(cliente.password, pass);

        //ENVIO DAS CREDENCIAIS PARA O BACKEND
        sprintf(UTILIZADOR_FIFO_FINAL, UTILIZADOR, cliente.pid);

        if(access(UTILIZADOR_FIFO_FINAL, F_OK) == 0) {
            printf("\n[ERRO] Esse utilizador ja existe\n");
            exit(0);
        }

        mkfifo(UTILIZADOR_FIFO_FINAL, 0666);

        utilizador_fd = open(UTILIZADOR_FIFO_FINAL, O_RDWR); //receber a msg de login
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

        /*sinal_fd = open(SINAL_FIFO, O_RDWR | O_NONBLOCK);
        if (sinal_fd == -1)
        {
            perror("\nErro ao abrir fifo dos sinais\n");
            exit(EXIT_FAILURE);
        }*/

        printf("nome: %s\n", cliente.nome);
        printf("password: %s\n", cliente.password);
        printf("pid: %d\n", cliente.pid);
        printf("backend_fd: %d\n", backend_fd);

        //ENVIO DAS CREDENCIAIS PARA O BACKEND
        int size = write(backend_fd, &(cliente), sizeof(cliente)); //envia as credenciais
        if(size <= 0){
            printf("\n[ERRO] Erro no envio do username e da password\n");
        }

        while(1){

            tv.tv_sec = 5;
            tv.tv_usec = 0;

            FD_ZERO(&read_fds);
            FD_SET(0, &read_fds);
            FD_SET(utilizador_fd, &read_fds);
            FD_SET(sinal_fd, &read_fds);

            nfd = select(utilizador_fd + 1, &read_fds, NULL, NULL, &tv);

            if(nfd == -1){
                printf("\nNada a receber\n");
                exit(0);
            }
            
            if(nfd == 0){
                printf("\n Estou a espera de comandos ou de mensagem do backend\n");
            }

            if(FD_ISSET(0, &read_fds)){ 
                //Aqui esta a escuta de comandos do utilizador
                fgets(cliente.comando, TAM_MAX, stdin);
                write(backend_fd, &cliente, sizeof(cliente));
            }
            
            if(FD_ISSET(utilizador_fd, &read_fds)){
                //Aqui esta a escuta que algo seja escrito no pipe utilizador_fd

                //RECEBE MENSAGEM A CONFIRMAR QUE FOI LOGADO
                int size2 = read(utilizador_fd, &msgFromBackend, sizeof(msgFromBackend));
                if(size2 < 0){
                    perror("Erro ao ler no pipe\n");
                }

                if(strcmp(msgFromBackend.msg, "Usuario Valido\n") == 0){
                    printf("Login feito com sucesso\n");
                    cliente.is_logged_in = 1;
                }
                else if(strcmp(msgFromBackend.msg, "[ERRO] Utilizador nao existe/password invalida\n") == 0){
                    printf("Login invalido\n");
                }else if(strcmp(msgFromBackend.msg, "\n[ERRO] Usuario ja esta loggado\n") == 0){
                    printf("Usuario ja se encontra loggado\n");
                }

                cliente.hBeat = msgFromBackend.hBeat;

                if(pthread_create(&thread, NULL, &enviaHEARTBEATorMSG, &(cliente)) != 0)
                    return -1;
            }/*else if(FD_ISSET(sinal_fd, &read_fds)){
            }*/

        }
            
    }
    //close(backend_fd);
    return 0;

}