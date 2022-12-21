#include "../frontend_files/frontend.h"
#include "../general.h"

#ifndef BACKEND_H
#define BACKEND_H

int max(int a, int b);
void commandHelp();
void commandsAdministrador();
ambientVars* getAmbientVariables(Backend* backend);
Itens* readItens(Backend* backend);
void openPromoter(Backend* backend);
void interface(Backend* backend);
char* verificaUser(Backend* backend, Clientes aux);

#endif

