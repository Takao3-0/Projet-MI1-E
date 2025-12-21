#ifndef ARBREC_H
#define ARBREC_H
#include "head.h"
#include "type.h"
#include "AVL.h"


typedef struct AC
{
    struct NodeL *node;

    struct AC * enfant;
    struct AC * frere;  

}AC, *pAC;





pNodeL creerNode(char *e);
pNodeL InsertionNode(pNodeL parent, pNodeL assign);

pAC creerAC(pNodeL info);
void freeAC(pAC a);
void InsertionAC(pAC parent, pAC child);

#endif
