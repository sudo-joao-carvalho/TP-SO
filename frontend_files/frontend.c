#include "frontend.h"
#include "../general.h"
#include "../backend_files/users_lib.h"

int backend_fd;
int utilizador_fd;
int sinal_fd;

void siguser2_handler(){
    printf("\n\t\tBackend terminado\n");
    unlink(UTILIZADOR_FIFO_FINAL);
    exit(EXIT_FAILURE);
}

void sigterm_handler(){
    printf("Login invalido\n");
    unlink(UTILIZADOR_FIFO_FINAL);
    exit(EXIT_FAILURE);
}

void sigquit_handler(){
    printf("User Terminado\n");
    unlink(UTILIZADOR_FIFO_FINAL);
    exit(EXIT_FAILURE);
}

void sigint_handler(){
    printf("\nSaiu\n");
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

void readCommands(char* CommandM, Clientes aux){

    char command[TAM_MAX];
    char firstCommand[10];
    char* token;

    fflush(stdin);

    //printf("Insira o comando que pretende executar: ");
    //fgets(command, TAM_MAX, stdin);

    token = strtok(CommandM, " \n");

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

            write(backend_fd, &aux, sizeof(aux));

            //sell mota1 automoveis 10 20 100
            //sell mota2 automoveis 10 20 100
            //sell mota3 automoveis 10 20 100

            //sell mota1 automoveis 10 20 20
            //sell mota2 automoveis 10 20 20
            //sell mota3 automoveis 10 20 20
        }else if(wordCounts < 6){
            printf("[ERRO] Numero de argumentos invalido\n");
            printf("[FORMATO] sell <nome-item> <categoria> <preço-base> <preço-compre-já> <duração>\n");
        }else if(wordCounts > 6){
            printf("[ERRO] Numero de argumentos invalido\n");
            printf("[FORMATO] sell <nome-item> <categoria> <preço-base> <preço-compre-já> <duração>\n");
        }

    }else if(strcmp(firstCommand, "list") == 0){

        if(wordCounts == 1){

            write(backend_fd, &aux, sizeof(aux));

            //list
        }else if(wordCounts < 1){
            printf("[ERRO] Numero de argumentos invalido\n");
            printf("[FORMATO] list\n");
        }else if(wordCounts > 1){
            printf("[ERRO] Numero de argumentos invalido\n");
            printf("[FORMATO] list\n");
        }

    }else if(strcmp(firstCommand, "licat") == 0){

        if(wordCounts == 2){

            write(backend_fd, &aux, sizeof(aux));

            //licat desporto
        }else if(wordCounts < 2){
            printf("[ERRO] Numero de argumentos invalido\n");
            printf("[FORMATO] licat <nome-categoria\n");
        }else if(wordCounts > 2){
            printf("[ERRO] Numero de argumentos invalido\n");
            printf("[FORMATO] licat <nome-categoria\n");
        }

    }else if(strcmp(firstCommand, "lisel") == 0){
            
        if(wordCounts == 2){

            write(backend_fd, &aux, sizeof(aux));

            //lisel joaoc
        }else if(wordCounts < 2){
            printf("[ERRO] Numero de argumentos invalido\n");
            printf("[FORMATO] lisel <username do vendedor>\n");
        }else if(wordCounts > 2){
            printf("[ERRO] Numero de argumentos invalido\n");
            printf("[FORMATO] lisel <username do vendedor>\n");
        }

    }else if(strcmp(firstCommand, "lival") == 0){
            
        if(wordCounts == 2){

            write(backend_fd, &aux, sizeof(aux));

            //lival 1000
        }else if(wordCounts < 2){
            printf("[ERRO] Numero de argumentos invalido\n");
            printf("[FORMATO] lival <preço-máximo>\n");
        }else if(wordCounts > 2){
            printf("[ERRO] Numero de argumentos invalido\n");
            printf("[FORMATO] lival <preço-máximo>\n");
        }

    }else if(strcmp(firstCommand, "litime") == 0){
            
        if(wordCounts == 2){

            write(backend_fd, &aux, sizeof(aux));

            //litime 250
        }else if(wordCounts < 2){
            printf("[ERRO] Numero de argumentos invalido\n");
            printf("[FORMATO] litime <hora-em-segundos>\n");
        }else if(wordCounts > 2){
            printf("[ERRO] Numero de argumentos invalido\n");
            printf("[FORMATO] litime <hora-em-segundos>\n");
        }

    }else if(strcmp(firstCommand, "time") == 0){
            
        if(wordCounts == 1){

            write(backend_fd, &aux, sizeof(aux));

            //time
        }else if(wordCounts < 1){
            printf("[ERRO] Numero de argumentos invalido\n");
            printf("[FORMATO] time\n");
        }else if(wordCounts > 1){
            printf("[ERRO] Numero de argumentos invalido\n");
            printf("[FORMATO] time\n");
        }

    }else if(strcmp(firstCommand, "buy") == 0){
        
        if(wordCounts == 3){

            write(backend_fd, &aux, sizeof(aux));

            //buy 1 100
        }else if(wordCounts < 3){
            printf("[ERRO] Numero de argumentos invalido\n");
            printf("[FORMATO] buy <id> <valor>\n");
        }else if(wordCounts > 3){
            printf("[ERRO] Numero de argumentos invalido\n");
            printf("[FORMATO] buy <id> <valor>\n");
        }

    }else if(strcmp(firstCommand, "cash") == 0){

        if(wordCounts == 1){

            write(backend_fd, &aux, sizeof(aux));

            //cash
        }else if(wordCounts < 1){
            printf("[ERRO] Numero de argumentos invalido\n");
            printf("[FORMATO] cash\n");
        }else if(wordCounts > 1){
            printf("[ERRO] Numero de argumentos invalido\n");
            printf("[FORMATO] cash\n");
        }

    }else if(strcmp(firstCommand, "add") == 0){
            
        if(wordCounts == 2){

            write(backend_fd, &aux, sizeof(aux));

            //add 100
        }else if(wordCounts < 2){
            printf("[ERRO] Numero de argumentos invalido\n");
            printf("[FORMATO] add <valor>\n");
        }else if(wordCounts > 2){
            printf("[ERRO] Numero de argumentos invalido\n");
            printf("[FORMATO] add <valor>\n");
        }

    }else if(strcmp(firstCommand, "help") == 0){

        if(wordCounts == 1){

            commandHelp();

        }else if(wordCounts < 1){
            printf("[ERRO] Numero de argumentos invalido\n");
            printf("[FORMATO] help\n");
        }else if(wordCounts > 1){
            printf("[ERRO] Numero de argumentos invalido\n");
            printf("[FORMATO] help\n");
        }

    }else if(strcmp(firstCommand, "exit") == 0){

        if(wordCounts == 1){

            write(backend_fd, &aux, sizeof(aux));

            //exit
        }else if(wordCounts < 1){
            printf("[ERRO] Numero de argumentos invalido\n");
            printf("[FORMATO] exit\n");
        }else if(wordCounts > 1){
            printf("[ERRO] Numero de argumentos invalido\n");
            printf("[FORMATO] exit\n");
        }
            
    }else
        printf("[ERRO] Comando invalido\n\n");
    

}

void* enviaHEARTBEAT(void* msgHeartBeat){

    Clientes* pMsgHeartBeat = (Clientes*) msgHeartBeat;
    int aux = pMsgHeartBeat->pid;

    while(1){
    //while(strcmp(pMsgHeartBeat->comando, "exit") != 0){
        sleep(pMsgHeartBeat->hBeat);
        //pthread_mutex_lock(&pMsgHeartBeat->m);
            sinal_fd = open(SINAL_FIFO, O_RDWR | O_NONBLOCK);
            write(sinal_fd, &aux, sizeof(aux));
        //pthread_mutex_unlock(&pMsgHeartBeat->m);
        close(sinal_fd);
    }

    //pthread_exit(NULL);

}

void parseCommands(Clientes* cliente, char* message){

    char firstCommand[10];
    char command[TAM_LIST];
    char* token;
    int saldo;
    int tempo;

    fflush(stdin);

    strcpy(command, message);
    token = strtok(command, " \n");

    int wordCounts = 0;
    while(token != NULL){

        if(wordCounts == 0){
            strcpy(firstCommand, token);
        }

        if(strcmp(firstCommand, "Add") == 0){
            if(wordCounts == 3){
                saldo = atoi(token);
                cliente->saldo = saldo;
                printf("Saldo atualizado %d", cliente->saldo);
                break;
            }
        }

        if(strcmp(firstCommand, "Cash") == 0){
            if(wordCounts == 1){
                saldo = atoi(token);
                cliente->saldo = saldo;
                printf("Saldo atual %d", cliente->saldo);
                break;
            }
        }

        if(strcmp(firstCommand, "Time") == 0){
            if(wordCounts == 1){
                tempo = atoi(token);
                printf("Tempo atual (em segundos): %d", tempo);
            }
        }

        if(strcmp(firstCommand, "LIST") == 0){
            if(wordCounts == 0){
                printf("\n%s", message);
            }
        }

        if(strcmp(firstCommand, "LICAT") == 0){
            if(wordCounts == 0){
                printf("\n%s", message);
            }
        }

        if(strcmp(firstCommand, "LISEL") == 0){
            if(wordCounts == 0){
                printf("\n%s", message);
            }
        }

        if(strcmp(firstCommand, "LIVAL") == 0){
            if(wordCounts == 0){
                printf("\n%s", message);
            }
        }

        if(strcmp(firstCommand, "LITIME") == 0){
            if(wordCounts == 0){
                printf("\n%s", message);
            }
        }

        if(strcmp(firstCommand, "Objeto") == 0){
            if(wordCounts == 0){
                printf("\n\t%s\n", message);
            }
        }
        if(strcmp(firstCommand, "Ninguem") == 0){
            if(wordCounts == 0){
                printf("\n\t%s", message);
            }
        }
        wordCounts++;

        token = strtok(NULL, " ");
    }

}

int main(int argc, char** argv){

    char* user = argv[1];
    char* pass = argv[2];
    char* command;
    char msg[TAM_MAX] = {'\0'};
    char saldoString[TAM_MAX] = {'\0'};
    Clientes cliente;
    int nfd;
    fd_set read_fds;
    struct timeval tv;
    pthread_t thread_hb;
    pthread_t thread_inactivityMSG;
    pthread_t thread_recebeUserWithCommad;
    //pthread_mutex_init(&cliente.m, NULL);
    dataMSG msgFromBackend;
    cliente.tempo_log = 0;
    cliente.is_logged_in = 0;

    signal(SIGTERM, sigterm_handler);
    signal(SIGQUIT, sigquit_handler);
    signal(SIGINT, sigint_handler);
    signal(SIGUSR2, siguser2_handler);
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
        strcpy(cliente.comando, msg);

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

        /*printf("nome: %s\n", cliente.nome);
        printf("password: %s\n", cliente.password);
        printf("pid: %d\n", cliente.pid);
        printf("backend_fd: %d\n", backend_fd);*/

        //ENVIO DAS CREDENCIAIS PARA O BACKEND
        int size = write(backend_fd, &(cliente), sizeof(cliente)); //envia as credenciais
        if(size <= 0){
            printf("\n[ERRO] Erro no envio do username e da password\n");
        }

        cliente.hBeat = atoi(getenv("HEARTBEAT"));

        if(pthread_create(&thread_hb, NULL, &enviaHEARTBEAT, &(cliente)) != 0)
            return -1;

        while(1){

            tv.tv_sec = 5;
            tv.tv_usec = 0;

            FD_ZERO(&read_fds);
            FD_SET(0, &read_fds);
            FD_SET(utilizador_fd, &read_fds);
            FD_SET(backend_fd, &read_fds);

            nfd = select(max(backend_fd, utilizador_fd) + 1, &read_fds, NULL, NULL, &tv);

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
                //printf("cliente.comando: %s\n", cliente.comando);
                cliente.tempo_log = 0;
                readCommands(cliente.comando, cliente);

            }
            
            if(FD_ISSET(utilizador_fd, &read_fds)){
                //Aqui esta a escuta que algo seja escrito no pipe utilizador_fd

                //RECEBE MENSAGENS DO BACKEND
                int size2 = read(utilizador_fd, &msgFromBackend, sizeof(msgFromBackend));
                if(size2 < 0){
                    perror("Erro ao ler no pipe\n");
                }

                cliente.hBeat = msgFromBackend.hBeat;

                if(cliente.is_logged_in == 0){
                    if(strcmp(msgFromBackend.msg, "Usuario Valido\n") == 0){
                        printf("Login feito com sucesso\n");
                        cliente.is_logged_in = 1;
                    }
                    else if(strcmp(msgFromBackend.msg, "[ERRO] Utilizador nao existe/password invalida\n") == 0){
                        printf("\tLogin invalido\n");
                        close(utilizador_fd);
                    }else if(strcmp(msgFromBackend.msg, "\n[ERRO] Usuario ja esta loggado\n") == 0){
                        printf("\tUsuario ja se encontra loggado\n");
                        close(utilizador_fd);
                    }else if(strcmp(msgFromBackend.msg, "Utilizador kickado por inatividade\n") == 0){
                        printf("\tUtilizador kickado por inatividade\n");
                        close(utilizador_fd);
                    }
                }

                //printf("\nmsgFromBackend.msg: {%s}\n", msgFromBackend.msg);

                if(cliente.is_logged_in == 1){

                    if(cliente.pid == msgFromBackend.pid){

                        //printf("msgFromBackend.msg: %s", msgFromBackend.msg);

                        if(strcmp(msgFromBackend.msg, "Item adquirido\n") == 0){
                            printf("Item adquirido\n");
                            //close(utilizador_fd);
                        }else if(strcmp(msgFromBackend.msg, "Licitacao feita\n") == 0){
                            printf("Licitacao feita\n");
                            //close(utilizador_fd);
                        }else if(strcmp(msgFromBackend.msg, "\n\tInsira um valor maior que o preco base do item\n") == 0){
                            printf("\n\tInsira um valor maior que o preco base do item\n");
                            //close(utilizador_fd);
                        }else if(strcmp(msgFromBackend.msg, "\nItem nao existente\n") == 0){
                            printf("\nItem nao existente\n");
                            //close(utilizador_fd);
                        }else if(strcmp(msgFromBackend.msg, "Backend Encerrou") == 0){
                            printf("\n\t\tBackend Encerrou\n");
                            //close(utilizador_fd);
                        }else if(strcmp(msgFromBackend.msg, "Novo Item a venda. (use o comando list para ver)") == 0){
                            printf("\n\tNovo Item a venda. (use o comando list para ver)\n");
                        }else{
                            parseCommands(&cliente, msgFromBackend.msg);
                            //printf("Saldo Atualizado: %d\n", cliente.saldo);

                        }

                    }   
                }

            }

        }

            
    }
    pthread_join(thread_hb, NULL);
    //pthread_mutex_destroy(&(cliente.m));
    //close(backend_fd);
    return 0;

}