#include "head.h"


/*

Cahier des charges 

On va mettre dans un arbre avec comme racine notre usine








*/







int leaks(FILE * fUsine, char *IDUsine)
{
    if(!fUsine) return 2; //Fichier vide 

    char line[128];
    char ID[128];
    bool usine_true = false;

    while(fgets(line, sizeof(line), fUsine) && !usine_true)
    {
        sscanf(line, "%[^;]", ID);
        if (strcmp(ID, IDUsine) == 0) usine_true = true;
    }
    if (!usine_true) return -1; //L'usine n'existe pas! 
}