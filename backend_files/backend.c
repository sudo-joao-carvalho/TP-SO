#include "backend.h"
#include "users_lib.h"

int backend_fd;
int utilizador_fd;
int sinal_fd;
int clientesCounter = 0;
int itensCounter = 0;

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

void executeCommandExit(Backend* backend, Clientes* aux){

    for(int i = 0; i < clientesCounter; i++){
        if(backend->clientes[i].pid == aux->pid){
            printf("\n\tUser %s saiu da plataforma\n", backend->clientes[i].nome);
            kill(backend->clientes[i].pid, SIGQUIT);
            removeUser(backend, backend->clientes[i]);
            clientesCounter--;
        }
    }

}

void executeCommandAdd(Backend* backend, Clientes* aux){

    char firstCommand[10];
    char message[TAM_MAX] = {"\0"};
    char* token;
    int valor;
    dataMSG buyStatus;
    buyStatus.hBeat = backend->aVars->HEARTBEAT;
    buyStatus.pid = aux->pid;
    strcpy(buyStatus.msg, message);

    sprintf(UTILIZADOR_FIFO_FINAL, UTILIZADOR, aux->pid); 
    utilizador_fd = open(UTILIZADOR_FIFO_FINAL, O_WRONLY);


    token = strtok(aux->comando, " \n");

    int wordCounts = 0;
    while(token != NULL){
        if(wordCounts == 0){
            strcpy(firstCommand, token);
        }

        if(wordCounts == 1){
            valor = atoi(token);
        }

        wordCounts++;

        token = strtok(NULL, " ");
    }

    for(int i = 0; i < clientesCounter; i++){
        if(strcmp(backend->clientes[i].nome, aux->nome) == 0){
            backend->clientes[i].saldo += valor;

            updateUserBalance(backend->clientes[i].nome, backend->clientes[i].saldo);
            saveUsersFile(backend->aVars->FUSERS);

            strcpy(message, "Saldo atualizado para %d");
            sprintf(buyStatus.msg, message, backend->clientes[i].saldo);
            printf("buyStatus.msg: %s\n", buyStatus.msg);
            write(utilizador_fd, &buyStatus, sizeof(buyStatus));

            close(utilizador_fd);
        }
    }


}

void executeCommandCash(Backend* backend, Clientes* cliente){

    char message[TAM_MAX] = {"\0"};
    dataMSG buyStatus;
    buyStatus.hBeat = backend->aVars->HEARTBEAT;
    buyStatus.pid = cliente->pid;
    strcpy(buyStatus.msg, message);

    sprintf(UTILIZADOR_FIFO_FINAL, UTILIZADOR, cliente->pid); 
    utilizador_fd = open(UTILIZADOR_FIFO_FINAL, O_WRONLY);

    strcpy(message, "Cash %d");
    sprintf(buyStatus.msg, message, cliente->saldo);

    write(utilizador_fd, &buyStatus, sizeof(buyStatus));
    close(utilizador_fd);

}

void executeCommandBuy(Backend* backend, Clientes* aux){

    char firstCommand[10];
    char message[TAM_MAX] = {"\0"};
    char* token;
    int id;
    int valor;
    dataMSG buyStatus;
    buyStatus.hBeat = backend->aVars->HEARTBEAT;
    buyStatus.pid = aux->pid;
    strcpy(buyStatus.msg, message);

    sprintf(UTILIZADOR_FIFO_FINAL, UTILIZADOR, aux->pid); 
    utilizador_fd = open(UTILIZADOR_FIFO_FINAL, O_WRONLY);

    token = strtok(aux->comando, " \n");

    int wordCounts = 0;
    while(token != NULL){
        if(wordCounts == 0){
            strcpy(firstCommand, token);
        }

        if(wordCounts == 1){
            id = atoi(token);
        }

        if(wordCounts == 2){
            valor = atoi(token);
        }
        wordCounts++;

        token = strtok(NULL, " ");
    }

    if(itensCounter > 0){
        for(int i = 0; i < itensCounter; i++){
            if(backend->itens[i].id == id){
                if(strcmp(backend->itens[i].nomeC, "nC") == 0 || valor <= backend->itens[i].comprar_ja){
                    if(valor >= backend->itens[i].preco_base){
                        if(aux->saldo >= valor){
                            if(valor == backend->itens[i].comprar_ja){ //compra imediata
                                strcpy(backend->itens[i].nomeC, aux->nome);
                                strcpy(buyStatus.msg, "Item adquirido\n");
                                write(utilizador_fd, &buyStatus, sizeof(buyStatus));

                                for(int j = 0; j < clientesCounter; j++){

                                    //saldo do que comprou
                                    if(strcmp(backend->clientes[j].nome, backend->itens[i].nomeC) == 0){
                                        aux->saldo -= valor;
                                        backend->clientes[j].saldo = aux->saldo;
                                        updateUserBalance(backend->clientes[j].nome, backend->clientes[j].saldo); 
                                        saveUsersFile(backend->aVars->FUSERS);
                                    }

                                    //saldo do que vendeu
                                    if(strcmp(backend->clientes[j].nome, backend->itens[i].nomeV) == 0){
                                        backend->clientes[j].saldo += valor;
                                        updateUserBalance(backend->clientes[j].nome, backend->clientes[j].saldo); 
                                        saveUsersFile(backend->aVars->FUSERS);
                                    }

                                }

                                removeItem(backend, &(backend->itens[i]));
                                itensCounter--;

                                close(utilizador_fd);

                            }else if(valor < backend->itens[i].comprar_ja){ //por licitacoes
                                strcpy(backend->itens[i].nomeC, aux->nome); //tracking de quem é ultimo licitador
                                backend->itens[i].preco_base = valor;
                                strcpy(buyStatus.msg, "Licitacao feita\n");
                                write(utilizador_fd, &buyStatus, sizeof(buyStatus));

                                close(utilizador_fd);
                            }
                        }else{
                            strcpy(buyStatus.msg, "\n\tSaldo Insuficiente\n");
                            write(utilizador_fd, &buyStatus, sizeof(buyStatus));
                            close(utilizador_fd);
                        }
                    }else{
                        strcpy(buyStatus.msg, "\n\tInsira um valor maior que o preco base do item\n");
                        write(utilizador_fd, &buyStatus, sizeof(buyStatus));
                        close(utilizador_fd);
                    }
                    
                }else{
                    strcpy(buyStatus.msg, "\n\tInsira um valor maior que o preco base do item\n");
                    write(utilizador_fd, &buyStatus, sizeof(buyStatus));
                    close(utilizador_fd);
                }

            }else{
                if(i == itensCounter - 1){
                    strcpy(buyStatus.msg, "\nItem nao existente\n");
                    write(utilizador_fd, &buyStatus, sizeof(buyStatus));
                    close(utilizador_fd);
                }else continue;
            }
        }
    }else{
        strcpy(buyStatus.msg, "\nNao existem items em leilao\n");
        write(utilizador_fd, &buyStatus, sizeof(buyStatus));
        close(utilizador_fd);
    }

}

void executeCommandTime(Backend* backend, Clientes* cliente){

    char message[TAM_MAX] = {"\0"};
    dataMSG buyStatus;
    buyStatus.hBeat = backend->aVars->HEARTBEAT;
    buyStatus.pid = cliente->pid;
    strcpy(buyStatus.msg, message);

    sprintf(UTILIZADOR_FIFO_FINAL, UTILIZADOR, cliente->pid); 
    utilizador_fd = open(UTILIZADOR_FIFO_FINAL, O_WRONLY);

    strcpy(message, "Time %d");
    sprintf(buyStatus.msg, message, backend->tempo_run);

    write(utilizador_fd, &buyStatus, sizeof(buyStatus));
    close(utilizador_fd);
}

void executeCommandLitime(Backend* backend, Clientes* cliente){

    char firstCommand[10];
    char* token;
    int tempo;
    char message[TAM_LIST] = {"\0"};
    dataMSG buyStatus;
    buyStatus.hBeat = backend->aVars->HEARTBEAT;
    buyStatus.pid = cliente->pid;

    token = strtok(cliente->comando, " \n");

    int wordCounts = 0;
    while(token != NULL){
        if(wordCounts == 0){
            strcpy(firstCommand, token);
        }

        if(wordCounts == 1){
            tempo = atoi(token);
        }
        wordCounts++;

        token = strtok(NULL, " ");
    }

    sprintf(UTILIZADOR_FIFO_FINAL, UTILIZADOR, cliente->pid); 
    utilizador_fd = open(UTILIZADOR_FIFO_FINAL, O_WRONLY);

    strcpy(buyStatus.msg, "LITIME");

    for(int i = 0; i < itensCounter; i++){
        if(backend->itens[i].tempo >= tempo){
            sprintf(message, "\nItem %d  Nome: %s  Categoria: %s  Preco Base: %d  Comprar Ja: %d  Tempo: %d  Nome Vendedor: %s  Nome Comprador: %s\n", backend->itens[i].id, backend->itens[i].nome, backend->itens[i].categoria, backend->itens[i].preco_base, backend->itens[i].comprar_ja, backend->itens[i].tempo, backend->itens[i].nomeV, backend->itens[i].nomeC);
            strcat(buyStatus.msg, message);
        }else continue;
    }

    write(utilizador_fd, &buyStatus, sizeof(buyStatus));
    close(utilizador_fd);
}

void executeCommandLival(Backend* backend, Clientes* cliente){

    char firstCommand[10];
    char* token;
    int valor;
    char message[TAM_LIST] = {"\0"};
    dataMSG buyStatus;
    buyStatus.hBeat = backend->aVars->HEARTBEAT;
    buyStatus.pid = cliente->pid;

    token = strtok(cliente->comando, " \n");

    int wordCounts = 0;
    while(token != NULL){
        if(wordCounts == 0){
            strcpy(firstCommand, token);
        }

        if(wordCounts == 1){
            valor = atoi(token);
        }
        wordCounts++;

        token = strtok(NULL, " ");
    }

    sprintf(UTILIZADOR_FIFO_FINAL, UTILIZADOR, cliente->pid); 
    utilizador_fd = open(UTILIZADOR_FIFO_FINAL, O_WRONLY);

    strcpy(buyStatus.msg, "LIVAL");

    for(int i = 0; i < itensCounter; i++){
        if(backend->itens[i].comprar_ja <= valor){
            sprintf(message, "\nItem %d  Nome: %s  Categoria: %s  Preco Base: %d  Comprar Ja: %d  Tempo: %d  Nome Vendedor: %s  Nome Comprador: %s\n", backend->itens[i].id, backend->itens[i].nome, backend->itens[i].categoria, backend->itens[i].preco_base, backend->itens[i].comprar_ja, backend->itens[i].tempo, backend->itens[i].nomeV, backend->itens[i].nomeC);
            strcat(buyStatus.msg, message);
        }else continue;
    }

    write(utilizador_fd, &buyStatus, sizeof(buyStatus));
    close(utilizador_fd);
}

void executeCommandLisel(Backend* backend, Clientes* cliente){

    char firstCommand[10];
    char* token;
    char vendedor[TAM_MAX] = {"\0"};
    char message[TAM_LIST] = {"\0"};
    dataMSG buyStatus;
    buyStatus.hBeat = backend->aVars->HEARTBEAT;
    buyStatus.pid = cliente->pid;

    token = strtok(cliente->comando, " \n");

    int wordCounts = 0;
    while(token != NULL){
        if(wordCounts == 0){
            strcpy(firstCommand, token);
        }

        if(wordCounts == 1){
            strcpy(vendedor, token);
        }
        wordCounts++;

        token = strtok(NULL, " ");
    }

    vendedor[strcspn(vendedor, "\n")] = 0;

    sprintf(UTILIZADOR_FIFO_FINAL, UTILIZADOR, cliente->pid); 
    utilizador_fd = open(UTILIZADOR_FIFO_FINAL, O_WRONLY);

    strcpy(buyStatus.msg, "LISEL");

    for(int i = 0; i < itensCounter; i++){
        if(strcmp(backend->itens[i].nomeV, vendedor) == 0){
            sprintf(message, "\nItem %d  Nome: %s  Categoria: %s  Preco Base: %d  Comprar Ja: %d  Tempo: %d  Nome Vendedor: %s  Nome Comprador: %s\n", backend->itens[i].id, backend->itens[i].nome, backend->itens[i].categoria, backend->itens[i].preco_base, backend->itens[i].comprar_ja, backend->itens[i].tempo, backend->itens[i].nomeV, backend->itens[i].nomeC);
            strcat(buyStatus.msg, message);
        }else continue;
    }

    write(utilizador_fd, &buyStatus, sizeof(buyStatus));
    close(utilizador_fd);
}

void executeCommandLicat(Backend* backend, Clientes* cliente){

    char firstCommand[10];
    char* token;
    char categoria[TAM_MAX] = {"\0"};
    char message[TAM_LIST] = {"\0"};
    dataMSG buyStatus;
    buyStatus.hBeat = backend->aVars->HEARTBEAT;
    buyStatus.pid = cliente->pid;

    token = strtok(cliente->comando, " \n");

    int wordCounts = 0;
    while(token != NULL){
        if(wordCounts == 0){
            strcpy(firstCommand, token);
        }

        if(wordCounts == 1){
            strcpy(categoria, token);
        }
        wordCounts++;

        token = strtok(NULL, " ");
    }

    categoria[strcspn(categoria, "\n")] = 0;

    sprintf(UTILIZADOR_FIFO_FINAL, UTILIZADOR, cliente->pid); 
    utilizador_fd = open(UTILIZADOR_FIFO_FINAL, O_WRONLY);

    strcpy(buyStatus.msg, "LICAT");

    for(int i = 0; i < itensCounter; i++){
        if(strcmp(backend->itens[i].categoria, categoria) == 0){
            sprintf(message, "\nItem %d  Nome: %s  Categoria: %s  Preco Base: %d  Comprar Ja: %d  Tempo: %d  Nome Vendedor: %s  Nome Comprador: %s\n", backend->itens[i].id, backend->itens[i].nome, backend->itens[i].categoria, backend->itens[i].preco_base, backend->itens[i].comprar_ja, backend->itens[i].tempo, backend->itens[i].nomeV, backend->itens[i].nomeC);
            strcat(buyStatus.msg, message);
        }else continue;
    }

    write(utilizador_fd, &buyStatus, sizeof(buyStatus));
    close(utilizador_fd);
}

void executeCommandList(Backend* backend, Clientes* cliente){

    char message[TAM_LIST] = {"\0"};
    dataMSG buyStatus;
    buyStatus.hBeat = backend->aVars->HEARTBEAT;
    buyStatus.pid = cliente->pid;

    sprintf(UTILIZADOR_FIFO_FINAL, UTILIZADOR, cliente->pid); 
    utilizador_fd = open(UTILIZADOR_FIFO_FINAL, O_WRONLY);

    strcpy(buyStatus.msg, "LIST");

    for(int i = 0; i < itensCounter; i++){
        sprintf(message, "\nItem %d  Nome: %s  Categoria: %s  Preco Base: %d  Comprar Ja: %d  Tempo: %d  Nome Vendedor: %s  Nome Comprador: %s\n", backend->itens[i].id, backend->itens[i].nome, backend->itens[i].categoria, backend->itens[i].preco_base, backend->itens[i].comprar_ja, backend->itens[i].tempo, backend->itens[i].nomeV, backend->itens[i].nomeC);
        strcat(buyStatus.msg, message);
    }

    write(utilizador_fd, &buyStatus, sizeof(buyStatus));
    close(utilizador_fd);
}

void executeCommandSell(Backend* backend, Clientes* aux){

    char firstCommand[10];
    char* token;
    char nome_item[TAM_MAX];
    char categoria[TAM_MAX];
    int preco_base;
    int preco_compre_ja;
    int duracao;
    dataMSG buyStatus;
    buyStatus.hBeat = backend->aVars->HEARTBEAT;

    token = strtok(aux->comando, " \n");

    int wordCounts = 0;
    while(token != NULL){
        if(wordCounts == 0){
            strcpy(firstCommand, token);
        }

        if(wordCounts == 1){
            strcpy(nome_item, token);
        }

        if(wordCounts == 2){
            strcpy(categoria, token);
        }

        if(wordCounts == 3){
            preco_base = atoi(token);
        }

        if(wordCounts == 4){
            preco_compre_ja = atoi(token);
        }

        if(wordCounts == 5){
            duracao = atoi(token);
        }
        wordCounts++;

        token = strtok(NULL, " ");
    }

    backend->itens[itensCounter - 1].id = itensCounter;
    strcpy(backend->itens[itensCounter - 1].nome, nome_item);
    strcpy(backend->itens[itensCounter - 1].categoria, categoria);
    backend->itens[itensCounter - 1].preco_base = preco_base;
    backend->itens[itensCounter - 1].comprar_ja = preco_compre_ja;
    backend->itens[itensCounter - 1].tempo = duracao;
    strcpy(backend->itens[itensCounter - 1].nomeV, aux->nome);
    strcpy(backend->itens[itensCounter - 1].nomeC, "nC");

    strcpy(buyStatus.msg, "Novo Item a venda. (use o comando list para ver)");

    for(int i = 0; i < clientesCounter; i++){
        buyStatus.pid = backend->clientes[i].pid;

        sprintf(UTILIZADOR_FIFO_FINAL, UTILIZADOR, backend->clientes[i].pid); 
        utilizador_fd = open(UTILIZADOR_FIFO_FINAL, O_WRONLY);

        write(utilizador_fd, &buyStatus, sizeof(buyStatus));
        close(utilizador_fd);

    }

}

void executeCommandsFromUser(Backend* backend, Clientes* cliente){

    char firstCommand[10];
    char comando[TAM_MAX];
    char* token;

    strcpy(comando, cliente->comando);

    token = strtok(comando, " \n");

    int wordCounts = 0;
    while(token != NULL){
        if(wordCounts == 0){
            strcpy(firstCommand, token);
        }
        wordCounts++;

        token = strtok(NULL, " ");
    }

    if(strcmp(firstCommand, "sell") == 0){
        itensCounter++;
        executeCommandSell(backend, cliente);
    }

    if(strcmp(firstCommand, "list") == 0){
        executeCommandList(backend, cliente);
    }

    if(strcmp(firstCommand, "licat") == 0){
        executeCommandLicat(backend, cliente);
    }

    if(strcmp(firstCommand, "lisel") == 0){
        executeCommandLisel(backend, cliente);
    }

    if(strcmp(firstCommand, "lival") == 0){
        executeCommandLival(backend, cliente);
    }

    if(strcmp(firstCommand, "litime") == 0){
        executeCommandLitime(backend, cliente);
    }

    if(strcmp(firstCommand, "time") == 0){
        executeCommandTime(backend, cliente);
    }

    if(strcmp(firstCommand, "buy") == 0){
        executeCommandBuy(backend, cliente);
    }

    if(strcmp(firstCommand, "cash") == 0){
        executeCommandCash(backend, cliente);
    }

    if(strcmp(firstCommand, "add") == 0){
        executeCommandAdd(backend, cliente);
    }

    if(strcmp(firstCommand, "exit") == 0){
        executeCommandExit(backend, cliente);
    }
}

void commandsAdministrador(Backend* backend, char* command){

    char firstCommand[10];
    char* token;
    char aux_username[TAM_MAX];

    fflush(stdin);

    token = strtok(command, " \n");

    int wordCounts = 0;
    while(token != NULL){
        if(wordCounts == 0){
            strcpy(firstCommand, token);
        }

        if(strcmp(firstCommand, "kick") == 0){
            if(wordCounts == 1){
                strcpy(aux_username, token);
            }
        }
        wordCounts++;

        token = strtok(NULL, " ");
    }

    if(strcmp(firstCommand, "users") == 0){

        if(wordCounts == 1){
            printf("Numero de argumentos valido\n");
            printf("COMANDO USERS EM EXECUCAO\n\n");

            for(int i = 0; i < clientesCounter; i++){
                printf("User %d: %s", i, backend->clientes[i].nome);
                printf("\tSaldo: %d\n", backend->clientes[i].saldo);
            }

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
            printf("COMANDO LIST EM EXECUCAO\n");

            if(itensCounter == 0){
                printf("\n\tNenhuma item a ser licitado neste momento\n");
            }else{
                for(int i = 0; i < itensCounter; i++){
                    printf("\nItem %d:\n", backend->itens[i].id);
                    printf("\tNome: %s\n", backend->itens[i].nome);
                    printf("\tCategoria: %s\n", backend->itens[i].categoria);
                    printf("\tPreco Base: %d\n", backend->itens[i].preco_base);
                    printf("\tComprar Ja: %d\n", backend->itens[i].comprar_ja);
                    printf("\tTempo: %d\n", backend->itens[i].tempo);
                    printf("\tNome Vendedor: %s\n", backend->itens[i].nomeV);
                    printf("\tNome Comprador: %s\n", backend->itens[i].nomeC);
                }
            }

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

            aux_username[strcspn(aux_username, "\n")] = 0;

            for(int i = 0; i < clientesCounter; i++){
                if(strcmp(backend->clientes[i].nome, aux_username) == 0){
                    printf("\nCliente %s kickado\n", backend->clientes[i].nome);
                    kill(backend->clientes[i].pid, SIGQUIT);
                    removeUser(backend, backend->clientes[i]);
                    clientesCounter--;
                }
            }

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

            for(int i = 0; i < clientesCounter; i++){
                printf("Encerrando cliente: %s\n", backend->clientes[i].nome);
            }

            printf("\n\t\tBackend encerrado\n");

            for(int i = 0; i < clientesCounter; i++){
                kill(backend->clientes[i].pid, SIGUSR2);
            }

            FILE *f = fopen(backend->aVars->FITEMS, "wt");

            if (!f)
            {
                printf("\nErro na abertura do ficheiro!\n");
                fclose(f);
                return;
            }

            for (int i = 0; i < itensCounter; i++)
            {
                if (backend->itens[i].id != 0)
                {
                    if (strcmp(backend->itens[i].nomeC, "nC") == 0)
                    {
                        strcpy(backend->itens[i].nomeC, "-");

                        fprintf(f, "%d %s %s %d %d %d %s %s\n",
                                backend->itens[i].id,
                                backend->itens[i].nome,
                                backend->itens[i].categoria,
                                backend->itens[i].preco_base,
                                backend->itens[i].comprar_ja,
                                backend->itens[i].tempo,
                                backend->itens[i].nomeV,
                                backend->itens[i].nomeC);
                    }
                    else
                    {
                        fprintf(f, "%d %s %s %d %d %d %s %s\n",
                                backend->itens[i].id,
                                backend->itens[i].nome,
                                backend->itens[i].categoria,
                                backend->itens[i].preco_base,
                                backend->itens[i].comprar_ja,
                                backend->itens[i].tempo,
                                backend->itens[i].nomeV,
                                backend->itens[i].nomeC);
                    }
                }
            }

            fclose(f);


            free(backend->itens);
            free(backend->aVars);
            free(backend->clientes);

            close(backend_fd);
            close(utilizador_fd);
            close(sinal_fd);
            unlink(BACKEND_FIFO);
            unlink(SINAL_FIFO);
            
            exit(0);

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

void readItens(Backend* backend){

    int i = 0;
    FILE* ptr;
    ptr = fopen(backend->aVars->FITEMS, "r");

    if (ptr == NULL) {
        printf("[ERRO] Ficheiro nao existe\n");
        //return backend->itens;
    }  
    
    while (!feof(ptr)){
        if(feof(ptr)){
            break;
        }

        fscanf(ptr," %d %s %s %d %d %d %s %s", &(backend->itens[i].id), backend->itens[i].nome, backend->itens[i].categoria, &(backend->itens[i].preco_base), &(backend->itens[i].comprar_ja), &(backend->itens[i].tempo), backend->itens[i].nomeV, backend->itens[i].nomeC);
         
        if(strcmp(backend->itens[i].nome, "n") == 0){
            return;
        }

        i++;
        itensCounter++;
    }

    fclose(ptr);
    //return backend->itens;

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
void resetaItens(Itens* item){

    item->id = 0;
    strcpy(item->nome, "n");
    strcpy(item->categoria, "c");
    item->preco_base = 0;
    item->comprar_ja = 0;
    item->tempo = 0;
    strcpy(item->nomeV, "nV");
    strcpy(item->nomeC, "nC");

}


void inicializaItens(Backend* backend){
    for(int i = 0; i < 30; i++){
        backend->itens[i].id = i + 1;
        strcpy(backend->itens[i].nome, "n");
        strcpy(backend->itens[i].categoria, "c");
        backend->itens[i].preco_base = 0;
        backend->itens[i].comprar_ja = 0;
        backend->itens[i].tempo = 100000000;
        strcpy(backend->itens[i].nomeV, "nV");
        strcpy(backend->itens[i].nomeC, "nC");
    }
}

void removeItem(Backend* backend, Itens* item){

    char message[TAM_LIST] = {"\0"};
    dataMSG buyStatus;
    buyStatus.hBeat = backend->aVars->HEARTBEAT;

    for(int i = 0; i < 30; i++){
        if(backend->itens[i].id == item->id){
            if(strcmp(backend->itens[i].nomeC, "nC") != 0){
                sprintf(message, "Objeto %s adquirido por %s", backend->itens[i].nome, backend->itens[i].nomeC);
                for(int i = 0; i < sizeof(buyStatus.msg); i++){ //Resetar a mensagem
                    buyStatus.msg[i] = '\0';
                }
                strcat(buyStatus.msg, message);

                for(int i = 0; i < clientesCounter; i++){
                    buyStatus.pid = backend->clientes[i].pid;

                    sprintf(UTILIZADOR_FIFO_FINAL, UTILIZADOR, backend->clientes[i].pid); 
                    utilizador_fd = open(UTILIZADOR_FIFO_FINAL, O_WRONLY);

                    write(utilizador_fd, &buyStatus, sizeof(buyStatus));
                    close(utilizador_fd);

                }
            }

            if(backend->itens[i].tempo == -1 && strcmp(backend->itens[i].nomeC, "nC") == 0){
                sprintf(message, "Ninguem licitou no item %s", backend->itens[i].nome);
                strcat(buyStatus.msg, message);

                for(int i = 0; i < clientesCounter; i++){
                    buyStatus.pid = backend->clientes[i].pid;

                    sprintf(UTILIZADOR_FIFO_FINAL, UTILIZADOR, backend->clientes[i].pid); 
                    utilizador_fd = open(UTILIZADOR_FIFO_FINAL, O_WRONLY);

                    write(utilizador_fd, &buyStatus, sizeof(buyStatus));
                    close(utilizador_fd);

                }
            }
            resetaItens(item);

            for(int j = i; j < 30; j++){
                backend->itens[j] = backend->itens[j + 1];
            }
        }
        
    }
}

void resetaCliente(Clientes* cliente){

    strcpy(cliente->nome, "n");
    strcpy(cliente->password, "p");
    cliente->pid = 0;
    cliente->saldo = 0;
    cliente->tempo_log = 0;
    strcpy(cliente->comando, "c");
    cliente->hBeat = 0;
    cliente->is_logged_in = 0;

}

void inicializaClientes(Backend* backend){
    for(int i = 0; i < 20; i++){
        strcpy(backend->clientes[i].nome, "n");
        strcpy(backend->clientes[i].password, "p");
        backend->clientes[i].pid = 0;
        backend->clientes[i].saldo = 0;
        backend->clientes[i].tempo_log = 0;
        strcpy(backend->clientes[i].comando, "c");
        backend->clientes[i].hBeat = 0;
        backend->clientes[i].is_logged_in = 0;
    }
}

void removeUser(Backend* backend, Clientes aux){

    for(int i = 0; i < 20; i++){
        if(backend->clientes[i].pid == aux.pid){

            resetaCliente(&(backend->clientes[i]));

            for(int j = i; j < 20; j++){
                backend->clientes[j] = backend->clientes[j + 1];
            }
        }
    }
}

void resetUserTimeWithPid(Backend* backend, int pid){
    
    for(int i = 0; i < clientesCounter; i++){
        if(backend->clientes[i].pid == pid){
            backend->clientes[i].tempo_log = 0;
        }
    }
}

void resetUserTime(Backend* backend, Clientes aux){
    
    for(int i = 0; i < clientesCounter; i++){
        if(backend->clientes[i].pid == aux.pid){
            backend->clientes[i].tempo_log = 0;
        }
    }
}

char* verificaUser(Backend* backend, Clientes aux){

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
            kill(aux.pid, SIGTERM);
            return "[ERRO] Utilizador nao existe/password invalida\n";
        }else if(isUserValid(aux.nome, aux.password) == 1){

            for(int i = 0; i < clientesCounter; i++){
                if(strcmp(backend->clientes[i].nome, aux.nome) == 0){
                    kill(aux.pid, SIGTERM);
                    return "\n[ERRO] Usuario ja esta loggado\n";
                }else continue;
            }

            aux.saldo = getUserBalance(aux.nome);
            backend->clientes[clientesCounter] = aux;

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

void* removeItemPorLicitacao(void* backend_aux){
    
    Backend* pBackend_aux = (Backend*) backend_aux;
    dataMSG resposta_t;
    resposta_t.hBeat = pBackend_aux->aVars->HEARTBEAT;

    while(1){

        for(int i = 0; i < itensCounter; i++){

            if(pBackend_aux->itens[i].tempo == -1){

                pthread_mutex_lock(&(pBackend_aux->m));

                    if(strcmp(pBackend_aux->itens[i].nomeC, "nC") == 0){
                        printf("Ninguem licitou no item %s", pBackend_aux->itens[i].nome);
                        removeItem(pBackend_aux, &(pBackend_aux->itens[i]));
                        itensCounter--;
                    }

                    for(int j = 0; j < clientesCounter; j++){
                        if(strcmp(pBackend_aux->clientes[j].nome, pBackend_aux->itens[i].nomeC) == 0){
                            resposta_t.pid = pBackend_aux->clientes[j].pid;

                            //saldo do que comprou
                            pBackend_aux->clientes[j].saldo = pBackend_aux->clientes[j].saldo - pBackend_aux->itens[i].preco_base;
                            updateUserBalance(pBackend_aux->clientes[j].nome, pBackend_aux->clientes[j].saldo);
                            saveUsersFile(pBackend_aux->aVars->FUSERS);

                            //close(utilizador_fd);
                            removeItem(pBackend_aux, &(pBackend_aux->itens[i]));
                            itensCounter--;
                        }

                        //saldo do que vendeu
                        if(strcmp(pBackend_aux->clientes[j].nome, pBackend_aux->itens[i].nomeV) == 0){
                            pBackend_aux->clientes[j].saldo += pBackend_aux->itens[i].preco_base;
                            updateUserBalance(pBackend_aux->clientes[j].nome, pBackend_aux->clientes[j].saldo); 
                            saveUsersFile(pBackend_aux->aVars->FUSERS);
                        }
                    pthread_mutex_unlock(&(pBackend_aux->m));
                }
            }

        }

    }

    pthread_exit(NULL);
}

void* inactivityThread(void* msgHeartBeat){

    Backend* pMsgHeartBeat = (Backend*) msgHeartBeat;
    dataMSG resposta_t;
    char messageI[100] = "Utilizador kickado por inatividade\n";

    while(1){
        sleep(1);
        pMsgHeartBeat->tempo_run++;

        if(itensCounter > 0)
            for(int i = 0; i < itensCounter; i++){
                pMsgHeartBeat->itens[i].tempo--;
            }

        pthread_mutex_lock(&(pMsgHeartBeat->m));
            for(int i = 0; i < clientesCounter; i++){
                if(pMsgHeartBeat->clientes[i].pid != 0){ //verifica que o user existe
                    pMsgHeartBeat->clientes[i].tempo_log++; //aumenta o tempo de log in

                    if(pMsgHeartBeat->clientes[i].tempo_log > pMsgHeartBeat->aVars->HEARTBEAT + 2){
                        strcpy(resposta_t.msg, messageI);

                        printf("\nCliente %s foi removido da plataforma\n", pMsgHeartBeat->clientes[i].nome);

                        kill(pMsgHeartBeat->clientes[i].pid, SIGINT);
                        removeUser(pMsgHeartBeat, pMsgHeartBeat->clientes[i]);
                        clientesCounter--;
                        break;
                    }
                }
            }
        pthread_mutex_lock(&(pMsgHeartBeat->m));

    }
    pthread_exit(NULL);

}


int main(int argc, char** argv){

    Backend backend;
    backend.itens = malloc(30 * sizeof(*backend.itens));
    backend.aVars = malloc(sizeof(*backend.aVars));
    backend.clientes = malloc(20 * sizeof(*backend.clientes));
    Clientes aux;
    int nfd;
    fd_set read_fds;
    struct timeval tv;
    char* clienteValidoMsg;
    dataMSG resposta;
    pthread_t thread_inacitvity;
    pthread_t thread_removeItemVendidoPorLicitacoes;
    pthread_mutex_init(&backend.m, NULL);
    aux.is_logged_in = 0;
    char command[TAM_MAX];

    //CARREGA LOGO AS VARS DE AMBIENTE
    backend.aVars = getAmbientVariables(&backend);
    inicializaClientes(&backend);
    inicializaItens(&backend);

    //CARREGA ITENS DE FITEMS
    readItens(&backend);
    /*for(int i = 0; backend.itens[i].id != '\0'; i++){
        printf("\n%d %s %s %d %d %d %s %s\n", backend.itens[i].id, backend.itens[i].nome, backend.itens[i].categoria, backend.itens[i].preco_base, backend.itens[i].comprar_ja, backend.itens[i].tempo, backend.itens[i].nomeV, backend.itens[i].nomeC);
    }*/

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
    printf("FIFO Backend Criado...\n");

    if(mkfifo(SINAL_FIFO, 0666) == -1){
        if(errno == EEXIST){ //existe apenas um backend
            printf("\n[ERRO] Servidor em execução ou fifo ja existe\n");
            return -1;
        }
        printf("\n[ERRO] Erro na criacao do fifo do backend\n");
        return -1;
    }
    printf("FIFO Sinais Criado...\n");

    //find . -type p -delete

    backend_fd = open(BACKEND_FIFO, O_RDWR);
    if(backend_fd == -1){
        printf("\n[ERRO] Erro ao abrir o fifo do backend");
        exit(EXIT_FAILURE);
    }

    sinal_fd = open(SINAL_FIFO, O_RDWR | O_NONBLOCK);
    if (sinal_fd == -1)
    {
        perror("\nErro ao abrir fifo dos sinais\n");
        exit(EXIT_FAILURE);
    }

    if(pthread_create(&thread_inacitvity, NULL, &inactivityThread, &(backend)) != 0)
        return -1;

    if(pthread_create(&thread_removeItemVendidoPorLicitacoes, NULL, &removeItemPorLicitacao, &(backend)) != 0)
        return -1;

    while(1){
        //interface(/*textPp, itens, aVars*/&backend);
        tv.tv_sec = 5;
        tv.tv_usec = 0;

        FD_ZERO(&read_fds);
        FD_SET(0, &read_fds);
        FD_SET(backend_fd, &read_fds);
        FD_SET(sinal_fd, &read_fds);

        nfd = select(max(backend_fd, sinal_fd) + 1, &read_fds, NULL, NULL, &tv);
        if(nfd == -1){
            printf("\nNada a receber\n");
            exit(0);
        }
        
        if(nfd == 0){
            printf("\n Estou a espera de comandos ou de utilizadores\n");
        }

        if(FD_ISSET(0, &read_fds)){
            //Aqui esta a escuta pelos comandos introduzidos pelo administrador
            fgets(command, TAM_MAX, stdin);
            commandsAdministrador(&backend, command);

        }
        
        if(FD_ISSET(backend_fd, &read_fds)){
            //Aqui esta a escuta dos utilizadores que vai receber pelo named_pipe
            read(backend_fd, &aux, sizeof(aux)); //ler o cliente para uma estrutura auxiliar para verificar se é um usuario valido e assim n ter de o adicionar a estrutura de clientes caso seja invalido

            if(aux.is_logged_in == 0){

                clienteValidoMsg = verificaUser(&backend, aux);
                strcpy(resposta.msg, clienteValidoMsg);
                resposta.hBeat = backend.aVars->HEARTBEAT;

                //RECEBE AS CREDENCIAIS DOS USERS
                if(strcmp(clienteValidoMsg, "Usuario Valido\n") == 0){
                    printf("\nUtilizador %s logado com sucesso\n", backend.clientes[clientesCounter].nome);
                    //printf("\n recebi o username [%s] e a password[%s]", backend.clientes[clientesCounter].nome, backend.clientes[clientesCounter].password);
                    aux.is_logged_in = 1;
                    backend.clientes[clientesCounter].is_logged_in = 1;

                }

                //ENVIA A RESPOSTA DE VERIFICACAO DE LOGIN AOS USERS
                sprintf(UTILIZADOR_FIFO_FINAL, UTILIZADOR, aux.pid); 
                utilizador_fd = open(UTILIZADOR_FIFO_FINAL, O_WRONLY);
                if(utilizador_fd == -1){
                    perror("\n[ERRO] Erro ao abrir o fifo do utilizador");
                    exit(EXIT_FAILURE);
                }

                resposta.pid = getpid();

                int s2 = write (utilizador_fd, &resposta, sizeof(resposta));
                if(s2 < 0){
                    printf("Erro ao escrever no pipe\n");
                }
                close(utilizador_fd);

                clientesCounter++;

            }else if(aux.is_logged_in == 1){
                aux.saldo = getUserBalance(aux.nome);
                printf("\nCOMANDO de %s: %s\n", aux.nome, aux.comando);

                executeCommandsFromUser(&backend, &aux);
            }

        }
        
        if(FD_ISSET(sinal_fd, &read_fds)){

            int pid;

            int a = read(sinal_fd, &pid, sizeof(pid));

            if(a == sizeof(pid)){
                for(int i = 0; i < clientesCounter; i++){
                    if(backend.clientes[i].pid == pid){
                        printf("\nHeartBeat de %s\n", backend.clientes[i].nome);
                        resetUserTimeWithPid(&backend, pid);
                    }
                }
            }

        }
    }

    pthread_join(thread_inacitvity, NULL);
    pthread_join(thread_removeItemVendidoPorLicitacoes, NULL);
    pthread_mutex_destroy(&backend.m);
    free(backend.itens);
    return 0;

}
