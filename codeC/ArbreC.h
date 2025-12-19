#ifndef ARBREC_H
#define ARBREC_H
#include "head.h"
#include "type.h"
#include "AVL.h"

typedef struct ArbreClassique
{
    struct NodeL *Node;

    struct ArbreClassique *F;
    struct ArbreClassique *E;
} ArbreClassique, *pAC;


pAC creerArbreClassique(pNodeL node);

pAC InsertionAC(pAC Reseau);

#endif
