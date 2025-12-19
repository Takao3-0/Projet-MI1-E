#include "ArbreC.h"
#include "AVL.h"


//Partie ARBRE CLASSIQUE pour le calcul des fuites


pNodeL creerNode(char *e, AVLKey mode)
{
    pNodeL nouveau = malloc(sizeof(NodeL));
    if(nouveau)
    {
        nouveau->ID = strdup(e);
        CHECK_MALLOC(nouveau->ID, free(nouveau->ID); free(nouveau));

        nouveau->leak = nouveau->volume_recu = 0;
    }
}

pNodeL InsertionNode(pNodeL parent, pNodeL assign)
{
    if(parent)
    {
        pNodeL enfant = parent->enfant;
        if(!enfant) parent->enfant = assign;
        else 
        {
            assign->frere = enfant;
            parent->enfant = assign;
        }
    }
    else return NULL;
}









