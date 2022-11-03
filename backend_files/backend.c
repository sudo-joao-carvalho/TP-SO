#include "backend.h"

int main(int argc, char** argv){

    char msgPromotor[TAM];

    int id = fork();

    if(id < 0){
        printf("[ERRO] Promotor nao foi criado com sucesso\n");
        return -4;
    }else if(id == 0){
        execl("/Users/joaocarvalho/Desktop/Universidade/2oAno/SO/TP/TP-SO/promotor_files/promotor", "./promotor", NULL);
    }else if(id > 0){
        fgets(msgPromotor, TAM, stdin);
        printf("%s", msgPromotor);
    }
    

}