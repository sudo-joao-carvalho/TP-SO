#include "promotor.h"

int main(int argc, char** argv){

    char msg[TAM];
    ptrHandlerPromotor textPp = malloc(sizeof(HandlerPromotor));

    pipe(textPp->fd);

    printf("Qual o texto que pretende mandar: ");
    fgets(msg, TAM, stdin);

    close(0);
    dup(textPp->fd[0]);
    close(textPp->fd[0]);
    close(textPp->fd[1]);

    //printf("\n\n[MSG] %s\n\n", msg);

    //RETOMAR
    close(textPp->fd[0]);
    write(textPp->fd[1], msg, sizeof(msg));

    return 0;

}