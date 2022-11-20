#include "../frontend_files/frontend.h"
#include "../general.h"

#ifndef BACKEND_H
#define BACKEND_H

typedef struct HandlerPromotor{
    int fd[2];
} HandlerPromotor, *ptrHandlerPromotor;

void commandHelp();
void commandsAdministrador();
ptrAmbientVars getAmbientVariables(ptrAmbientVars aVars);
ptrItens readItens(ptrItens i, ptrAmbientVars aVars);
ptrHandlerPromotor openPromoter(ptrHandlerPromotor pP, ptrAmbientVars aVars);
void interface(ptrHandlerPromotor textPp, ptrItens itens, ptrAmbientVars aVars);

#endif

