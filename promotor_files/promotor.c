#include "promotor.h"

int main(int argc, char** argv){

    char msg[TAM];
    char *token;
    ptrPromotor p = malloc(sizeof(Promotor));

    //printf("Qual o texto que pretende mandar: ");
    //fgets(msg, TAM, stdin);
    //printf("%s", p->message);

    strcpy(p->message, "ola 10 100");

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

    printf("%s", p->message);// printa a mensagem do promotor para o backend

    return 0;

}