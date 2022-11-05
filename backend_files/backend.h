#include "../frontend_files/frontend.h"

#ifndef BACKEND_H
#define BACKEND_H

typedef struct HandlerPromotor{
    int fd[2];
} HandlerPromotor, *ptrHandlerPromotor;

void readItens(ptrItens i);
void commandsAdministrador();
void commandHelp();

#endif

