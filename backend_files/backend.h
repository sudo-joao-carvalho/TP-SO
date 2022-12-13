#include "../frontend_files/frontend.h"
#include "../general.h"

#ifndef BACKEND_H
#define BACKEND_H

void commandHelp();
void commandsAdministrador();
ptrAmbientVars getAmbientVariables(Backend* backend);
ptrItens readItens(Backend* backend);
void openPromoter(Backend* backend);
void interface(Backend* backend);

#endif

