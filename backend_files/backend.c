#include "backend.h"
#include "users_lib.h"

int max(int a, int b){
    return (a > b) ? a : b;
}

void commandHelp(){

    printf("\n\n******************  Admin. Commands List  ******************\n\n");
    printf("--> users\n");
    printf("--> list\n");
    printf("--> kick <username>\n");
    printf("--> prom\n");
    printf("--> reprom\n");
    printf("--> cancel <nome-do-executavel-do-promotor>\n");
    printf("--> help\n");
    printf("--> close\n");

}

void commandsAdministrador(){

    char command[TAM_MAX];
    char firstCommand[10];
    char* token;

    fflush(stdin);

    printf("Insira o comando de administrador que pretende executar: ");
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

     if(strcmp(firstCommand, "users") == 0){

        if(wordCounts == 1){
            printf("Numero de argumentos valido\n");
            printf("COMANDO USERS EM EXECUCAO\n");
        }else if(wordCounts < 1){
            printf("[ERRO] Numero de argumentos invalido\n");
            printf("[FORMATO] users\n");
        }else if(wordCounts > 1){
            printf("[ERRO] Numero de argumentos invalido\n");
            printf("[FORMATO] users\n");
        }

    }else if(strcmp(firstCommand, "list") == 0){

        if(wordCounts == 1){
            printf("Numero de argumentos valido\n");
            printf("COMANDO USERS EM EXECUCAO\n");
        }else if(wordCounts < 1){
            printf("[ERRO] Numero de argumentos invalido\n");
            printf("[FORMATO] list\n");
        }else if(wordCounts > 1){
            printf("[ERRO] Numero de argumentos invalido\n");
            printf("[FORMATO] list\n");
        }

    }else if(strcmp(firstCommand, "kick") == 0){

        if(wordCounts == 2){
            printf("Numero de argumentos valido\n");
            printf("COMANDO KICK EM EXECUCAO\n");
        }else if(wordCounts < 2){
            printf("[ERRO] Numero de argumentos invalido\n");
            printf("[FORMATO] kick <username>\n");
        }else if(wordCounts > 2){
            printf("[ERRO] Numero de argumentos invalido\n");
            printf("[FORMATO] kick <username>\n");
        }

    }else if(strcmp(firstCommand, "prom") == 0){

        if(wordCounts == 1){
            printf("Numero de argumentos valido\n");
            printf("COMANDO PROM EM EXECUCAO\n");
        }else if(wordCounts < 1){
            printf("[ERRO] Numero de argumentos invalido\n");
            printf("[FORMATO] prom\n");
        }else if(wordCounts > 1){
            printf("[ERRO] Numero de argumentos invalido\n");
            printf("[FORMATO] prom\n");
        }

    }else if(strcmp(firstCommand, "reprom") == 0){

        if(wordCounts == 1){
            printf("Numero de argumentos valido\n");
            printf("COMANDO REPROM EM EXECUCAO\n");
        }else if(wordCounts < 1){
            printf("[ERRO] Numero de argumentos invalido\n");
            printf("[FORMATO] reprom\n");
        }else if(wordCounts > 1){
            printf("[ERRO] Numero de argumentos invalido\n");
            printf("[FORMATO] reprom\n");
        }

    }else if(strcmp(firstCommand, "cancel") == 0){

        if(wordCounts == 2){
            printf("Numero de argumentos valido\n");
            printf("COMANDO CANCEL EM EXECUCAO\n");
        }else if(wordCounts < 2){
            printf("[ERRO] Numero de argumentos invalido\n");
            printf("[FORMATO] cancel <nome-do-executavel-do-promotor>\n");
        }else if(wordCounts > 2){
            printf("[ERRO] Numero de argumentos invalido\n");
            printf("[FORMATO] cancel <nome-do-executavel-do-promotor>\n");
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

    }else if(strcmp(firstCommand, "close") == 0){

        if(wordCounts == 1){
            printf("Numero de argumentos valido\n");
            printf("COMANDO CLOSE EM EXECUCAO\n");
        }else if(wordCounts < 1){
            printf("[ERRO] Numero de argumentos invalido\n");
            printf("[FORMATO] close\n");
        }else if(wordCounts > 1){
            printf("[ERRO] Numero de argumentos invalido\n");
            printf("[FORMATO] close\n");
        }

    }else{
        printf("[ERRO] Comando invalido\n\n");
    }

}

ambientVars* getAmbientVariables(Backend* backend){

    if(getenv("FPROMOTERS") == NULL){
        printf("\n[ERRO] Variavel de ambiente FPROMOTORES nao existente\n");
        exit(0);
    }
    backend->aVars->FPROMOTERS = getenv("FPROMOTERS");

    if(getenv("FUSERS") == NULL){
        printf("\n[ERRO] Variavel de ambiente FUSERS nao existente\n");
        exit(0);
    }
    backend->aVars->FUSERS = getenv("FUSERS");

    if(getenv("FITEMS") == NULL){
        printf("\n[ERRO] Variavel de ambiente FITEMS nao existente\n");
        exit(0);
    }
    backend->aVars->FITEMS = getenv("FITEMS");

    if(getenv("HEARTBEAT") == NULL){
        printf("\n[ERRO] Variavel de ambiente FITEMS nao existente\n");
        exit(0);
    }
    backend->aVars->HEARTBEAT = atoi(getenv("HEARTBEAT"));

    /*printf("\n[FPROMOTERS] %s", backend.aVars->FPROMOTERS);
    printf("\n[FUSERS] %s", backend.aVars->FUSERS);
    printf("\n[FITEMS] %s\n", backend.aVars->FITEMS);
    printf("\n[HEARTBEAT] %D\n", backend.aVars->HEARTBEAT);*/

    return backend->aVars;

}

Itens* readItens(Backend* backend){

    int i = 0;
    FILE* ptr;
    ptr = fopen(backend->aVars->FITEMS, "r");

    if (ptr == NULL) {
        printf("[ERRO] Ficheiro nao existe\n");
        return backend->itens;
    }  
    
    while (!feof(ptr)){
        if(feof(ptr)){
            break;
        }

        fscanf(ptr," %d %s %s %d %d %d %s %s", &(backend->itens[i].id), backend->itens[i].nome, backend->itens[i].categoria, &(backend->itens[i].preco_base), &(backend->itens[i].comprar_ja), &(backend->itens[i].tempo), backend->itens[i].nomeV, backend->itens[i].nomeC);
         
        i++;
    }

    fclose(ptr);
    return backend->itens;

 }   

void openPromoter(Backend* backend){

    char msgPromotor[TAM_MAX];
    char path[100];
    char ff[TAM_MAX] = "../promotor_files/";
    char fff[TAM_MAX] = "./";
    int fd[2];

    strcpy(path, strcat(ff, backend->aVars->FPROMOTERS));
    strcat(fff, backend->aVars->FPROMOTERS);

    pipe(fd);

    int id = fork();

    if(id < 0){
        printf("[ERRO] Promotor nao foi criado com sucesso\n");
        return ;
    }else if(id == 0){
        close(1); //fecha o stdout no file descriptor
        dup(fd[1]); //duplica o stdout
        close(fd[0]); //fecha o antigo
        close(fd[1]); // fecha a outra ponta do pipe
        
        execl(path, fff, NULL);
        exit(0);
    }else if(id > 0){
        int size = read(fd[0], msgPromotor, sizeof(msgPromotor)); //lê o que recebe do printf do promotor atraves do pipe
        
        if(size > 0){
            close(fd[1]); //fecha a ponta do pipe onde foi escrito
            printf("%s", msgPromotor); //printa a mensagem do promotor

            /*union sigval xpto;
            sigqueue(id, SIGUSR1, xpto);*/

            //working
            kill(id, SIGKILL);
            wait(&id);
        }else printf("\nMensagem nao lida\n");

        return ;
    }

    return ;
}

/*void interface(Backend* backend){

    //Leitura dos comandos 1a meta
    char initCommand[TAM_MAX];

    fflush(stdin);

    printf("\nDeseja testar que funcionalidade? <comandos> || <execuçao promotor> || <utilizador> || <itens> || <help> || <exit>\n");
    fgets(initCommand, TAM_MAX, stdin);
    initCommand[strcspn(initCommand, "\n")] = '\0';

    if(strcmp(initCommand, "comandos") == 0){
        commandsAdministrador();
    }else if(strcmp(initCommand, "execucao promotor") == 0){

        if(strcmp(backend->aVars->FPROMOTERS, "black_friday") == 0 || strcmp(backend->aVars->FPROMOTERS, "promotor_oficial") == 0){
            openPromoter(backend);
        }else{
            printf("[ERRO] Nome do ficheiro de promotores errado\n");
            return;
        }
            
    }else if(strcmp(initCommand, "utilizador") == 0){
        fflush(stdin);

        ptrClientes clientes;

        int nUsers = loadUsersFile(backend->aVars->FUSERS);
        clientes = malloc(nUsers * sizeof(Clientes));

        if(nUsers > 0){
            printf("Ficheiro lido com sucesso\n");
        }else{
            printf("[ERRO] Erro ao ler o ficheiro");
            return ;
        }

        if(clientes == NULL){
            printf("[ERRO] Memoria nao alocada");
            free(clientes);
            return ;
        }

        for(int i = 0; i < nUsers; i++){
            printf("Insira o username: ");
            scanf(" %s", clientes[i].nome);
            printf("Insira uma password: ");
            scanf(" %s", clientes[i].password);

            if(isUserValid(clientes[i].nome, clientes[i].password) == 0){
                printf("[ERRO] Utilizador nao existe/password invalida\n");
            }else if(isUserValid(clientes[i].nome, clientes[i].password) == 1){
                printf("Usuário Valido\n");

                clientes[i].saldo = getUserBalance(clientes[i].nome);
                clientes[i].saldo -= 1;
                updateUserBalance(clientes[i].nome, clientes[i].saldo);

                saveUsersFile(backend->aVars->FUSERS);

            }else if(isUserValid(clientes[i].nome, clientes[i].password) == -1){
                printf("[ERRO]");
                return ;
            }
        }

        free(clientes);
        return ;
    }else if(strcmp(initCommand, "itens") == 0){
        backend->itens = readItens(backend);

        for(int i = 0; backend->itens[i].id != '\0'; i++){
            printf("\n%d %s %s %d %d %d %s %s\n", backend->itens[i].id, backend->itens[i].nome, backend->itens[i].categoria, backend->itens[i].preco_base, backend->itens[i].comprar_ja, backend->itens[i].tempo, backend->itens[i].nomeV, backend->itens[i].nomeC);
        }

        return ;
    }else if(strcmp(initCommand, "help") == 0){
        commandHelp();
        return ;
    }else if(strcmp(initCommand, "exit") == 0){
        exit(0);
    }else{
        printf("\n\t[ERRO] Comando errado");
        return ;
    }
    //Leitura dos comandos 1a meta
    
}*/

char* verificaUser(Backend* backend, Clientes aux, int clientesCounter){

    fflush(stdin);

    int nUsers = loadUsersFile(backend->aVars->FUSERS);

    if(nUsers > 0){
        printf("Ficheiro lido com sucesso\n");
    }else{
        //printf("[ERRO] Erro ao ler o ficheiro");
        return "[ERRO] Erro ao ler o ficheiro";
    }

    if(clientesCounter <= 19){
        if(isUserValid(aux.nome, aux.password) == 0){
            return "[ERRO] Utilizador nao existe/password invalida\n";
        }else if(isUserValid(aux.nome, aux.password) == 1){

            for(int i = 0; i < clientesCounter; i++){
                if(strcmp(backend->clientes[i].nome, aux.nome) == 0){
                    //kill(aux.pid, SIGTERM); dar kill ao da nova execucao
                    return "\n[ERRO] Usuario ja esta loggado\n";
                }else continue;
            }

            backend->clientes[clientesCounter] = aux;
            backend->clientes[clientesCounter].saldo = getUserBalance(backend->clientes[clientesCounter].nome);

            //updateUserBalance(aux.nome, aux.nome);

            //saveUsersFile(backend.aVars.FUSERS);

            return "Usuario Valido\n";
            
        }else if(isUserValid(aux.nome, aux.password) == -1){
            return "[ERRO]";
        }
    }else
        printf("\nNumero maximo de utilizadores atingido\n");

    

    return "[ERRO]";
}

void* recebeHeartBeat(void* msgHeartBeat){

    Clientes* pMsgHeartBeat = (Clientes*) msgHeartBeat;

    //printf("ola");

    pthread_mutex_lock(&pMsgHeartBeat->m);
        printf("\nHEARTBEAT:  %s\n",  pMsgHeartBeat->msgHB);
    pthread_mutex_unlock(&pMsgHeartBeat->m);
  
    pthread_exit(NULL);

}


int main(int argc, char** argv){

    Backend backend;
    backend.itens = malloc(30 * sizeof(backend.itens));
    backend.aVars = malloc(sizeof(backend.aVars));
    backend.clientes = malloc(20 * sizeof(backend.clientes));
    Clientes aux;
    int clientesCounter = 0;
    int nfd;
    fd_set read_fds;
    struct timeval tv;
    char* clienteValidoMsg;
    dataMSG resposta;
    pthread_t thread[20];
    pthread_mutex_init(&backend.clientes->m, NULL);

    //CARREGA LOGO AS VARS DE AMBIENTE
    backend.aVars = getAmbientVariables(&backend);

    if(backend.itens == NULL){
        printf("[ERRO] Memoria nao alocada\n");
        free(backend.itens);
        return -1;
    }
    
    if(backend.aVars == NULL){
        printf("[ERRO] Memoria nao alocada\n");
        free(backend.itens);
        free(backend.aVars);
        return -1;
    }

    if(mkfifo(BACKEND_FIFO, 0666) == -1){
        if(errno == EEXIST){ //existe apenas um backend
            printf("\n[ERRO] Servidor em execução ou fifo ja existe\n");
            return -1;
        }
        printf("\n[ERRO] Erro na criacao do fifo do backend\n");
        return -1;
    }
    printf("FIFO Criado...\n");

    //find . -type p -delete

    int backend_fd = open(BACKEND_FIFO, O_RDONLY);
    if(backend_fd == -1){
        printf("\n[ERRO] Erro ao abrir o fifo do backend");
        exit(EXIT_FAILURE);
    }

    while(1){
        //interface(/*textPp, itens, aVars*/&backend);
        tv.tv_sec = 5;
        tv.tv_usec = 0;

        FD_ZERO(&read_fds);
        FD_SET(0, &read_fds);
        FD_SET(backend_fd, &read_fds);

        nfd = select(backend_fd + 1, &read_fds, NULL, NULL, &tv);
        if(nfd == -1){
            printf("\nNada a receber\n");
            exit(0);
        }
        
        if(nfd == 0){
            printf("\n Estou a espera de comandos ou de utilizadores\n");
        }

        if(FD_ISSET(0, &read_fds)){
            //Aqui esta a escuta pelos comandos introduzidos pelo administrador

        }else if(FD_ISSET(backend_fd, &read_fds)){
            //Aqui esta a escuta dos utilizadores que vai receber pelo named_pipe
            int size = read(backend_fd, &aux, sizeof(aux)); //ler o cliente para uma estrutura auxiliar para verificar se é um usuario valido e assim n ter de o adicionar a estrutura de clientes caso seja invalido
            
            if(size < 0){
                printf("\n[ERRO] Erro ao ler do pipe\n");
            }else if(size > 0){
                clienteValidoMsg = verificaUser(&backend, aux, clientesCounter);

                strcpy(resposta.msg, clienteValidoMsg);
                resposta.hBeat = backend.aVars->HEARTBEAT;

                //RECEBE AS CREDENCIAIS DOS USERS
                if(strcmp(clienteValidoMsg, "Usuario Valido\n") == 0){
                    printf("\nUTILIZADOR_%d", backend.clientes[clientesCounter].pid);
                    printf("\n recebi o username [%s] e a password[%s]", backend.clientes[clientesCounter].nome, backend.clientes[clientesCounter].password);
                    if (strcmp("sair\n", backend.clientes[clientesCounter].nome)==0){
                        close(backend_fd);
                        unlink (BACKEND_FIFO);
                        return 1;
                    }
                }

                //ENVIA A RESPOSTA DE VERIFICACAO DE LOGIN AOS USERS
                sprintf(UTILIZADOR_FIFO_FINAL, UTILIZADOR, aux.pid); //tem que mandar para o aux.pid pois caso o utilizador n exista ele n vai estar no array de users
                int utilizador_fd = open (UTILIZADOR_FIFO_FINAL, O_WRONLY | O_NONBLOCK);
                if(utilizador_fd == -1){
                    perror("\n[ERRO] Erro ao abrir o fifo do utilizador");
                    exit(EXIT_FAILURE);
                }

                resposta.pid = getpid();

                int s2 = write (utilizador_fd, &resposta, sizeof(resposta));
                if(s2 < 0){
                    printf("Erro ao escrever no pipe\n");
                }

                //POR ISTO DENTRO DO WHILE(STRCMP DO COMANDO QUE RECEBE COM EXIT) --> se o comando for exit ele para de mandar heartbeats e elimina da kick ao user
                //depois dar close(backend_fd) e unlink(BACKEND_FIFO)
                //RECEBE O HEARBEAT
                
                /*while(1){
                    for(int j = 0; j < clientesCounter; j++){
                        //aux.fd = backend_fd;
                        backend.clientes[j].fd = backend_fd;
                        //strcpy(backend.clientes[clientesCounter].msgHB, aux.msgHB);

                        //printf("A  %s  ", backend.clientes[clientesCounter].msgHB);
                        if(pthread_create(&thread[j], NULL, &recebeHeartBeat, &backend.clientes[j]) != 0)
                            return -1;
                    }

                    for(int j = 0; j < clientesCounter; j++){
                        if (pthread_join(thread[j], NULL) != 0){
                            return -1;
                        }
                    }
                }*/
                
                //sleep(backend.aVars->HEARTBEAT);

                int i = 0;
                while(i < backend.aVars->HEARTBEAT){
                    if(i == backend.aVars->HEARTBEAT - 1){
                        int s3 = read(backend_fd, &(aux), sizeof(aux)); //com aux da 1

                        strcpy(backend.clientes[clientesCounter].msgHB, aux.msgHB);
                        if(s3 < 0){
                            perror("\n[ERRO] Erro ao ler do pipeAAA\n");
                        }else if(s3 > 0){
                            printf("\nHEARTBEAT:  %s\n",  aux.msgHB);

                            i = 0;
                        }
                    }
                    i++;
                }

                /*int s3 = read(backend_fd, &(backend.clientes[clientesCounter]), sizeof(backend.clientes[clientesCounter]));
                if(s3 < 0){
                    perror("\n[ERRO] Erro ao ler do pipe\n");
                }else if(s3 > 0){
                    //aux.fd = backend_fd;
                    backend.clientes[clientesCounter].fd = backend_fd;

                    //printf("A  %s  ", backend.clientes[clientesCounter].msgHB);
                    for(int i = 0; i < clientesCounter; i++){
                        if(pthread_create(&thread[i], NULL, &recebeHeartBeat, &backend.clientes[i]) != 0)
                            return -1;
                    }
                }*/

                clientesCounter++;
            }
        }
    }
    pthread_mutex_destroy(&backend.clientes->m);
    free(backend.itens);
    return 0;

}
