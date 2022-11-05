#include "backend.h"

int main(int argc, char** argv){

    char msgPromotor[TAM];
    ptrHandlerPromotor textPp = malloc(sizeof(HandlerPromotor));
   
    //Leitura dos comandos 1a meta
    char initCommand[TAM];

    printf("Deseja testar que funcionalidade? <comandos> || <execuçao promotor> || <utilizador> || <itens> \n");
    scanf(" %s", initCommand);

    if(strcmp(initCommand, "comandos") == 0){
        if(readCommands() == false) return 0;
    }else if(strcmp(initCommand, "execucao") == 0){

        pipe(textPp->fd);

        int id = fork();

        if(id < 0){
        printf("[ERRO] Promotor nao foi criado com sucesso\n");
            return -4;
        }else if(id == 0){
            close(1); //fecha o stdout no file descriptor
            dup(textPp->fd[1]); //duplica o stdout
            close(textPp->fd[0]); //fecha o antigo
            close(textPp->fd[1]); // fecha a outra ponta do pipe

            execl("/Users/joaocarvalho/Desktop/Universidade/2oAno/SO/TP/TP-SO/promotor_files/promotor", "./promotor", NULL);
        }else if(id > 0){
            read(textPp->fd[0], msgPromotor, sizeof(msgPromotor)); //lê o que recebe do printf do promotor atraves do pipe
            close(textPp->fd[1]); //fecha a ponta do pipe onde foi escrito
            printf("%s", msgPromotor); //printa a mensagem do promotor
            return 0;
        }

    }else if(strcmp(initCommand, "utilizador") == 0){
        printf("\nutilizador\n");
        return 0;
    }else if(strcmp(initCommand, "itens") == 0){
        printf("\nitens\n");
        return 0;
    }else{
        printf("\n\t[ERRO] Comando errado");
        return -1;
    }
    //Leitura dos comandos 1a meta
    
    return 0;

}