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

ptrAmbientVars getAmbientVariables(ptrAmbientVars aVars){

    aVars->FPROMOTERS = getenv("FPROMOTERS");
    aVars->FUSERS = getenv("FUSERS");
    aVars->FITEMS = getenv("FITEMS");

    return aVars;

}

ptrItens readItens(ptrItens itens, ptrAmbientVars aVars){

    int i = 0;
    FILE* ptr;
    ptr = fopen(aVars->FITEMS, "r");

    if (ptr == NULL) {
        printf("[ERRO] Ficheiro nao existe\n");
        return itens;
    }  
    
    while (!feof(ptr)){
        if(feof(ptr)){
            break;
        }

        fscanf(ptr," %d %s %s %d %d %d %s %s", &(itens[i].id), itens[i].nome, itens[i].categoria, &(itens[i].preco_base), &(itens[i].comprar_ja), &(itens[i].tempo), itens[i].nomeV, itens[i].nomeC);
         
        i++;
    }

    fclose(ptr);
    return itens;

 }   

ptrHandlerPromotor openPromoter(ptrHandlerPromotor pP, ptrAmbientVars aVars){

    char msgPromotor[TAM];
    char path[100];
    char ff[TAM] = "../promotor_files/";
    char fff[TAM] = "./";

    strcpy(path, strcat(ff, aVars->FPROMOTERS));
    strcat(fff, aVars->FPROMOTERS);

    pipe(pP->fd);

    int id = fork();

    if(id < 0){
        printf("[ERRO] Promotor nao foi criado com sucesso\n");
        return NULL;
    }else if(id == 0){
        close(1); //fecha o stdout no file descriptor
        dup(pP->fd[1]); //duplica o stdout
        close(pP->fd[0]); //fecha o antigo
        close(pP->fd[1]); // fecha a outra ponta do pipe
        
        execl(path, fff, NULL);
    }else if(id > 0){
        read(pP->fd[0], msgPromotor, sizeof(msgPromotor)); //lê o que recebe do printf do promotor atraves do pipe
        close(pP->fd[1]); //fecha a ponta do pipe onde foi escrito
        printf("%s", msgPromotor); //printa a mensagem do promotor

        /*union sigval xpto;
        sigqueue(id, SIGUSR1, xpto);*/

        //working
        kill(id, SIGKILL);
        wait(&id);

        return 0;
    }

    return pP;
}

void interface(ptrHandlerPromotor textPp, ptrItens itens, ptrAmbientVars aVars){

    //Leitura dos comandos 1a meta
    char initCommand[TAM];

    fflush(stdin);

    printf("\nDeseja testar que funcionalidade? <comandos> || <execuçao promotor> || <utilizador> || <itens> || help || exit\n");
    fgets(initCommand, TAM, stdin);
    initCommand[strcspn(initCommand, "\n")] = '\0';

    if(strcmp(initCommand, "comandos") == 0){
        commandsAdministrador();
    }else if(strcmp(initCommand, "execucao promotor") == 0){

        if(strcmp(aVars->FPROMOTERS, "black_friday") == 0 || strcmp(aVars->FPROMOTERS, "promotor_oficial") == 0){
            textPp = openPromoter(textPp, aVars);
        }else{
            printf("[ERRO] Nome do ficheiro de promotores errado\n");
            return;
        }
            
    }else if(strcmp(initCommand, "utilizador") == 0){
        fflush(stdin);

        ptrClientes clientes;

        int nUsers = loadUsersFile(aVars->FUSERS);
        printf("[nUsers] %d", nUsers);
        clientes = malloc(nUsers * sizeof(Clientes));


        if(nUsers > 0){
            printf("Ficheiro lido com sucesso\n");
        }else{
            printf("[ERRO] Erro ao ler o ficheiro");
            return ;
        }
        for(int i = 0; i < nUsers; i++){
            printf("Insira o username: ");
            scanf(" %s", clientes[i].nome);
            printf("Insira uma password: ");
            scanf(" %s", clientes[i].password);
        }

        if(clientes == NULL){
            printf("[ERRO] Memoria nao alocada");
            free(clientes);
            return ;
        }

        for(int i = 0; i < nUsers; i++){
            if(isUserValid(clientes[i].nome, clientes[i].password) == 0){
                printf("[ERRO] Utilizador nao existe/password invalida\n");
            }else if(isUserValid(clientes[i].nome, clientes[i].password) == 1){
                printf("Usuário Valido\n");

                clientes[i].saldo = getUserBalance(clientes[i].nome);
                clientes[i].saldo -= 1;
                updateUserBalance(clientes[i].nome, clientes[i].saldo);

                saveUsersFile(aVars->FUSERS);

            }else if(isUserValid(clientes[i].nome, clientes[i].password) == -1){
                printf("[ERRO]");
                return ;
            }
        }

        free(clientes);
        return ;
    }else if(strcmp(initCommand, "itens") == 0){
        itens = readItens(itens, aVars);

        for(int i = 0; itens[i].id != '\0'; i++){
            printf("\n%d %s %s %d %d %d %s %s\n", itens[i].id, itens[i].nome, itens[i].categoria, itens[i].preco_base, itens[i].comprar_ja, itens[i].tempo, itens[i].nomeV, itens[i].nomeC);
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

    ptrHandlerPromotor textPp = malloc(sizeof(HandlerPromotor));
    ptrItens itens = malloc(30 * sizeof(Itens));
    ptrAmbientVars aVars = malloc(sizeof(ambientVars));

    if(textPp == NULL){
        printf("[ERRO] Memoria nao alocada\n");
        free(textPp);
        return -1;
    }

    if(itens == NULL){
        printf("[ERRO] Memoria nao alocada\n");
        free(textPp);
        free(itens);
        return -1;
    }
    
    if(aVars == NULL){
        printf("[ERRO] Memoria nao alocada\n");
        free(textPp);
        free(itens);
        free(aVars);
        return -1;
    }

    aVars = getAmbientVariables(aVars);

    while(1)
        interface(textPp, itens, aVars);

    free(textPp);
    free(itens);

    return 0;

}

//Duvidas alocar o espaco apra os cleintes dentro da verificacao se o comando for utilizador e no caso dos itens isso n acontece(sera que ha problema mais apra a frente)
//como fazer o execl noutros pcs devido ao path dos ficheiros