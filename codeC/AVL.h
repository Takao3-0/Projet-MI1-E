#ifndef AVL_H
#define AVL_H

#include "head.h"
#include "type.h"
/*typedef struct AVL
{
    char *ID;
    double Capacity_Max;
    double Total_Source_Vol;
    double Total_Real_Vol;

    struct AVL *fg;
    struct AVL *fd;

    int equi;
}AVL, *pAVL;*/

//Structure AVL Histo

typedef struct NodeH
{
    char *ID;
    double Capacity_Max;
    double Total_Source_Vol;
    double Total_Real_Vol;

}NodeH, *pNodeH;


//Structure AVL leaks


typedef struct NodeL {
    char *ID;
    double volume_recu;
    float leak; 
    struct AC *ac; //c'est cette ligne qui sert d'index
    
} NodeL, *pNodeL;



//Refonte de la structure AVL;



typedef struct AVL
{
    char *ID;

    AVLKey key;

    union 
    {
        NodeH *HistoPart;
        NodeL *LeaksPart;
    }data;
    
    struct AVL *fg;
    struct AVL *fd;

    int equi;

}AVL, *pAVL;



pAVL equilibreAVL(pAVL a);

/* AVL */
pAVL creerAVL(char *e/*Identifiant*/, AVLKey fkey);
pAVL recherche(pAVL a, char *e);
pAVL insertionAVL(pAVL a, char * e/*identifiant*/, int *h, AVLKey fkey);
pAVL equilibreAVL(pAVL a);

/* rotations */
pAVL rotation_gauche(pAVL a);
pAVL rotation_droite(pAVL a);
pAVL rotation_double_gauche(pAVL a);
pAVL rotation_double_droite(pAVL a);

/* suppression */
//pAVL sup_min(pAVL a, pAVL *minNode, int *h);
//pAVL suppression_AVL(pAVL a, const char *key, int *h);


/*Parcour*/

void parcoursprefixe(pAVL racine, FILE * returnfile, HistoMode mode);

void freeAVL(pAVL a);

#endif