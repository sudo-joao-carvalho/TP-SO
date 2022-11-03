#include "promotor.h"

int main(int argc, char** argv){

    char msg[TAM];
    ptrHandlerPromotor textPp = malloc(sizeof(HandlerPromotor));

    printf("Qual o texto que pretende mandar: ");
    fgets(msg, TAM, stdin);

    pipe(textPp->fd);

    close(0);
    dup(textPp->fd[0]);
    close(textPp->fd[0]);
    close(textPp->fd[1]);

    write(textPp->fd[1], msg, sizeof(msg));
    close(textPp->fd[0]);

    return 0;

}