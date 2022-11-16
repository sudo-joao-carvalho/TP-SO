#include "../frontend_files/frontend.h"
#include "../general.h"

#ifndef BACKEND_H
#define BACKEND_H

typedef struct HandlerPromotor{
    int fd[2];
} HandlerPromotor, *ptrHandlerPromotor;

ptrClientes readCLientes(ptrClientes clientes, char* nome_fich, int nUsers);
ptrItens readItens(ptrItens i, char* nome_fich);
void commandsAdministrador();
void commandHelp();
ptrHandlerPromotor communicationPipe(ptrHandlerPromotor pP, char* nomeFichPromotores);
void interface(ptrHandlerPromotor textPp, ptrItens itens);

#endif

