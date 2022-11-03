#include "promotor.h"

int main(int argc, char** argv){

    ptrHandlerPromotor textPp = malloc(sizeof(HandlerPromotor));

    pipe(textPp->fd);

    printf("ola mundo\n");

    return 0;

}