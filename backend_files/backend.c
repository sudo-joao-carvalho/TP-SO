#include "backend.h"
#include "users_lib.h"

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

    char command[TAM];
    char firstCommand[10];
    char* token;

    fflush(stdin);

    printf("Insira o comando de administrador que pretende executar: ");
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

ptrAmbientVars getAmbientVariables(/*ptrAmbientVars aVars*/Backend* backend){

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

    /*printf("\n[FPROMOTERS] %s", aVars->FPROMOTERS);
    printf("\n[FUSERS] %s", aVars->FUSERS);
    printf("\n[FITEMS] %s\n", aVars->FITEMS);*/

    return backend->aVars;

}

ptrItens readItens(/*ptrItens itens, ptrAmbientVars aVars*/Backend* backend){

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

void openPromoter(/*ptrHandlerPromotor pP, ptrAmbientVars aVars*/Backend* backend){

    char msgPromotor[TAM];
    char path[100];
    char ff[TAM] = "../promotor_files/";
    char fff[TAM] = "./";
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

void interface(/*ptrHandlerPromotor textPp, ptrItens itens, ptrAmbientVars aVars*/Backend* backend){

    //Leitura dos comandos 1a meta
    char initCommand[TAM];

    fflush(stdin);

    printf("\nDeseja testar que funcionalidade? <comandos> || <execuçao promotor> || <utilizador> || <itens> || <help> || <exit>\n");
    fgets(initCommand, TAM, stdin);
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
    
}

int main(int argc, char** argv){

    Backend backend;
    backend.itens = malloc(30 * sizeof(backend.itens));
    backend.aVars = malloc(sizeof(backend.aVars));
    //ptrHandlerPromotor textPp = malloc(sizeof(HandlerPromotor));
    //ptrItens itens = malloc(30 * sizeof(Itens));
    //ptrAmbientVars aVars = malloc(sizeof(ambientVars));

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

    /*if(mkfifo(BACKEND_FIFO, 0666) == -1){
        if(errno == EEXIST){
            printf("\n[ERRO] Servidor em execução ou fifo já existe\n");
        }
        printf("\n[ERRO] Erro na criacao do fifo do backend\n");
        return 0;
    }*/

    backend.aVars = getAmbientVariables(&backend);

    /*int backend_fd = open(BACKEND_FIFO,O_RDONLY);
    if(backend_fd == -1){
        printf("\n[ERRO] Erro no fifo do backend");
        exit(EXIT_FAILURE);
    }*/

    while(1)
        //interface(/*textPp, itens, aVars*/&backend);

        //int size;
    free(backend.itens);
    /*unlink(BACKEND_FIFO);
    close(backend_fd);*/
    return 0;

}