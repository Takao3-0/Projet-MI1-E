#ifndef ARBREC_H
#define ARBREC_H
#include "head.h"

typedef struct ArbreClassique
{
    char *id;

    double volume;
    double leak;

    struct ArbreClassique * next_bro;
    struct ArbreClassique * first_child;
} ArbreClassique, *pAC;


pAC creerArbreClassique(char *id, double leak, double vol);

#endif
