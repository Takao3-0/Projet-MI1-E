#include "ArbreC.h"
#include "AVL.h"


//Partie ARBRE CLASSIQUE pour le calcul des fuites

pAC creerArbreClassique(pNodeL node)
{
    pAC nouveau = malloc(sizeof(ArbreClassique));
    if(nouveau)
    {
        nouveau->Node = node;
        return nouveau;
    }
    else return NULL;
}


pAC InsertionAC(pAC Reseau)
{
    
}





