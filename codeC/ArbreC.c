#include "ArbreC.h"
#include "AVL.h"


//Partie ARBRE CLASSIQUE pour le calcul des fuites




pNodeL creerNode(char *e)
{
    pNodeL nouveau = malloc(sizeof(NodeL));
    if(nouveau)
    {
        nouveau->ID = strdup(e);
        CHECK_MALLOC(nouveau->ID, free(nouveau->ID); free(nouveau));


        nouveau->leak = nouveau->volume_recu = 0;
        return nouveau;
    }
    else 
    {
        free(nouveau);
        return NULL;
    }
}

pAC creerAC(pNodeL info)
{
    pAC a = malloc(sizeof(AC));
    if(a)
    {
        a->node = info;
        a->enfant = a->frere = NULL;
        return a;
    }
    else return NULL;
}


void InsertionAC(pAC parent, pAC child)
{
    if (!parent || !child) return;
    child->frere = parent->enfant;
    parent->enfant = child;
}





