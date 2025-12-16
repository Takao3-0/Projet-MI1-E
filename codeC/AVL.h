#ifndef AVL_H
#define AVL_H

#include "head.h"

typedef struct AVL
{
    char *ID;
    double Capacity_Max;
    double Total_Source_Vol;
    double Total_Real_Vol;

    struct AVL *fg;
    struct AVL *fd;

    int equi;
}AVL, *pAVL;

pAVL equilibreAVL(pAVL a);

/* AVL */
pAVL creerAVL(char *e);
pAVL recherche(pAVL a, char *e);
pAVL insertionAVL(pAVL a, char *e, int *h);
pAVL equilibreAVL(pAVL a);

/* rotations */
pAVL rotation_gauche(pAVL a);
pAVL rotation_droite(pAVL a);
pAVL rotation_double_gauche(pAVL a);
pAVL rotation_double_droite(pAVL a);

/* suppression */
pAVL sup_min(pAVL a, pAVL *minNode, int *h);
pAVL suppression_AVL(pAVL a, const char *key, int *h);


/*Parcour*/

void parcoursprefixe(pAVL racine,FILE * returnfile);

void suppressionAVL(pAVL a);

#endif