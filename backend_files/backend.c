#include "backend.h"

int main(int argc, char** argv){

    printf("\nentrei no backend\n");

    char msgPromotor[TAM];

    int id = fork();

    if(id < 0){
        printf("[ERRO] Promotor nao foi criado com sucesso\n");
        return -4;
    }else if(id == 0){
        //printf("Promotor criado com sucesso\n\n");
        //execl("/Users/joaocarvalho/Desktop/Universidade/2oAno/SO/TP/TP-SO/frontend_files/frontend", "./frontend", NULL);
        execl("/Users/joaocarvalho/Desktop/Universidade/2oAno/SO/TP/TP-SO/promotor_files/promotor", "./promotor", NULL);
    }else if(id > 0){
        printf("1o criar o promotor\n\n");
        fgets(msgPromotor, TAM, stdin);
        //printf("\ndepois de receber\n");
        printf("%s", msgPromotor);
    }
    

}