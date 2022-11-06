#include "../frontend_files/frontend.h"

#ifndef BACKEND_H
#define BACKEND_H

typedef struct HandlerPromotor{
    int fd[2];
} HandlerPromotor, *ptrHandlerPromotor;

ptrItens readItens(ptrItens i, char* nome_fich);
void commandsAdministrador();
void commandHelp();
ptrHandlerPromotor communicationPipe(ptrHandlerPromotor pP);

#endif

