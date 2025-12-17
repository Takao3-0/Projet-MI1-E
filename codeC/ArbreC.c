#include "ArbreC.h"


//Partie ARBRE CLASSIQUE pour le calcul des fuites

typedef struct ArbreClassique
{
    char *id;

    double volume;
    double leak;

    struct ArbreClassique * next_bro;
    struct ArbreClassique * first_child;
} ArbreClassique, *pAC;

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

