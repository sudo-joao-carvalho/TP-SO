#include "promotor.h"

int main(int argc, char** argv){

    char msg[TAM];
    char *token;
    ptrHandlerPromotor textPp = malloc(sizeof(HandlerPromotor));
    ptrPromotor p = malloc(sizeof(Promotor));

    printf("Qual o texto que pretende mandar: ");
    fgets(msg, TAM, stdin);

    int wordCounts = 0;
    token = strtok(msg, " \n");
    while(token != NULL){
        if(wordCounts == 0){
            strcpy(p->categoria, token);
        }

        if(wordCounts == 1){
            p->desconto = atoi(token);
        }

        if(wordCounts == 2){
            p->duracao = atoi(token);
        }
        wordCounts++;

        token = strtok(NULL, " ");
    }

    strcpy(p->message, msg);

    pipe(textPp->fd);

    close(0);
    dup(textPp->fd[0]);
    close(textPp->fd[0]);
    close(textPp->fd[1]);

    write(textPp->fd[1], msg, sizeof(msg));
    close(textPp->fd[0]);

    return 0;

}