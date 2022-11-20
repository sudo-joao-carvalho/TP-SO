#include "../frontend_files/frontend.h"
#include "../general.h"

#ifndef BACKEND_H
#define BACKEND_H

typedef struct HandlerPromotor{
    int fd[2];
} HandlerPromotor, *ptrHandlerPromotor;

ptrAmbientVars getAmbientVariables(ptrAmbientVars aVars);
ptrClientes readCLientes(ptrClientes clientes, ptrAmbientVars aVars, int nUsers);
ptrItens readItens(ptrItens i, ptrAmbientVars aVars);
void commandsAdministrador();
void commandHelp();
ptrHandlerPromotor openPromoter(ptrHandlerPromotor pP, ptrAmbientVars aVars);
void interface(ptrHandlerPromotor textPp, ptrItens itens, ptrAmbientVars aVars);

#endif

