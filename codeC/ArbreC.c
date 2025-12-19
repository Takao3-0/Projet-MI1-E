#include "ArbreC.h"


//Partie ARBRE CLASSIQUE pour le calcul des fuites

pAC creerArbreClassique(char *id, double leak, double vol)
{
    pAC nouveau = malloc(sizeof(ArbreClassique));
    if(nouveau)
    {
        nouveau->id = strdup(id);

        nouveau->volume = vol;
        nouveau->leak = leak;

        nouveau->next_bro = nouveau->first_child = NULL;
        return nouveau;
    }
    else return NULL;
}





