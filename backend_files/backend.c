#include "backend.h"
#include "users_lib.h"

//DUVIDA NOS ITENS: ao ler eles devem ser introduzimos por exemplo num array dinamico
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

ptrClientes readCLientes(ptrClientes clientes, char* nome_fich){

    FILE* file;
    int i = 0;
    file = fopen(nome_fich, "r");

    if (file == NULL) {
        printf("[ERRO] Ficheiro nao existe\n");
        return clientes;
    }  
    
    while (!feof(file)){
        if(feof(file)){
            break;
        }
        
        fscanf(file, "%s %s %d", clientes[i].nome, clientes[i].password, &(clientes[i].saldo));
        //printf("\n%s %s %d", clientes[i].nome, clientes[i].password, clientes[i].saldo);
        
        i++; 
    }
           
    fclose(file);
    return clientes;
    
}


ptrHandlerPromotor communicationPipe(ptrHandlerPromotor pP){

    char msgPromotor[TAM];

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

        //execl("/Users/joaocarvalho/Desktop/Universidade/2oAno/SO/TP/TP-SO/promotor_files/promotor", "./promotor", NULL);
        //execl("/Users/joaocarvalho/Desktop/Universidade/2oAno/SO/TP/TP-SO/promotor_files/promotor_oficial", "./promotor_oficial", NULL);
        //execl("/Users/joaocarvalho/Desktop/Universidade/2oAno/SO/TP/TP-SO/promotor_files/black_friday", "./black_fridayl", NULL);
        exit(0);
    }else if(id > 0){
        read(pP->fd[0], msgPromotor, sizeof(msgPromotor)); //lê o que recebe do printf do promotor atraves do pipe
        close(pP->fd[1]); //fecha a ponta do pipe onde foi escrito
        printf("%s", msgPromotor); //printa a mensagem do promotor
        return 0;
    }

    return pP;
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

ptrItens readItens(ptrItens itens, char* nome_fich){

    int i = 0;
    FILE* ptr;
    ptr = fopen(nome_fich, "r");

    if (ptr == NULL) {
        printf("[ERRO] Ficheiro nao existe\n");
        return itens;
    }  
    
    while (!feof(ptr)){
        if(feof(ptr)){
            break;
        }

        fscanf(ptr," %d %s %s %d %d %d %s %s", &(itens[i].id), itens[i].nome, itens[i].categoria, &(itens[i].preco_base), &(itens[i].comprar_ja), &(itens[i].tempo), itens[i].nomeV, itens[i].nomeC);
        //printf("\n%d %s %s %d %d %d %s %s\n", itens[i].id, itens[i].nome, itens[i].categoria, itens[i].preco_base, itens[i].comprar_ja, itens[i].tempo, itens[i].nomeV, itens[i].nomeC);
         
        i++;
    }

    //printf("i = %d", i);
    printf("ola");

    /*for(int j = 0; j < i; j++){
        printf("\n%d %s %s %d %d %d %s %s\n", itens[i].id, itens[i].nome, itens[i].categoria, itens[i].preco_base, itens[i].comprar_ja, itens[i].tempo, itens[i].nomeV, itens[i].nomeC);
    }*/
    

    fclose(ptr);
    return itens;

 }   

void interface(ptrHandlerPromotor textPp, ptrItens itens, ptrClientes clientes){

    //Leitura dos comandos 1a meta
    char initCommand[TAM];
    char nome_fich[TAM];
    char usersPath[] = "users.txt";

    printf("\nDeseja testar que funcionalidade? <comandos> || <execuçao promotor> || <utilizador> || <itens> || help\n");
    scanf(" %s", initCommand);

    if(strcmp(initCommand, "comandos") == 0){
        commandsAdministrador();
    }else if(strcmp(initCommand, "execucao") == 0){
        textPp = communicationPipe(textPp);
    }else if(strcmp(initCommand, "utilizador") == 0){
        int nUsers = loadUsersFile(usersPath);

        clientes = realloc(clientes, nUsers * sizeof(Clientes));
        clientes = readCLientes(clientes, usersPath);

        for(int i = 0; i < nUsers; i++){
            updateUserBalance(clientes[i].nome, clientes[i].saldo -= 1);
            printf("\n%s %s %d", clientes[i].nome, clientes[i].password, clientes[i].saldo);
        }

        saveUsersFile(usersPath);

        return ;
    }else if(strcmp(initCommand, "itens") == 0){
        printf("Qual o nome do ficheiro que deseja ler?\n");
        scanf(" %s", nome_fich);
        itens = readItens(itens, nome_fich);

        for(int i = 0; i < 2; i++){
            printf("\n%d %s %s %d %d %d %s %s\n", itens[i].id, itens[i].nome, itens[i].categoria, itens[i].preco_base, itens[i].comprar_ja, itens[i].tempo, itens[i].nomeV, itens[i].nomeC);
        }      

        return ;
    }else if(strcmp(initCommand, "help") == 0){
        commandHelp();
        return ;
    }else{
        printf("\n\t[ERRO] Comando errado");
        return ;
    }
    //Leitura dos comandos 1a meta
    
}

int main(int argc, char** argv){

    ptrHandlerPromotor textPp = malloc(sizeof(HandlerPromotor));
    ptrItens itens = malloc(30 * sizeof(Itens));
    ptrClientes clientes = malloc(sizeof(Clientes));

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

    if(clientes == NULL){
        printf("[ERRO] Memoria nao alocada\n");
        free(textPp);
        free(itens);
        free(clientes);
        return -1;
    }

    interface(textPp, itens, clientes);

    free(textPp);
    free(itens);
    //free(clientes); erro a dar free aos clientes

    return 0;

}