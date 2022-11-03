#include "backend.h"

int main(int argc, char** argv){

    prtHandlerPromotor textPp = malloc(sizeof(HandlerPromotor));

    pipe(textPp->fd);

    int id = fork();

    if(id < 0){
        printf("[ERRO] Promotor nao foi criado com sucesso\n");
        return -4;
    }else if(id == 0){
        printf("Promotor criado com sucesso\n\n");
        execl("../promotor_files/./promotor", "./promotor", NULL);
    }else if(id > 0){
        printf("1o criar o promotor\n\n");

    }
    

}