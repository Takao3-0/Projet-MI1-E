#include "head.h"
#include "histo.h"

/*

Cahier des charges 

    Ici on doit pouvoir comparer les données des usines.
        -On recupere les donnes des sources et usines.
            -On place ça dans un AVL.
                -AVL;
                -Sommer les capacités de captage/traitement pour chaque usine;
                    -Il faut identifier chaque source relié a une usine particuliere et sommer tout les volumes en direction de cette usine. 
                -Trier les usine par identifiant inverse????;
            -Le programme doit nous retourner un fichier CSV
                -Il servira à GnuPlot? via le script Shell.









    -Pour l'AVL
    Chaque noeud correcpond à une usine, pour obtenir la capacite max d'une usine il faut sommer tout les volumes provenant des sources.
    Dans un noeud on stocke 3 arg : max, src, real 
        Capacite max de l'usine, une valeur fixe qu'on trouve sur la ligne de l'usine
        Le volume capté, soit la somme des volumes de toutes les sources reliées à cette usine.
        La somme des volumes captés multipliée par le rendement   ???? mais les fuites sont au niveau de l'usine ou entre les sources et l'usine???
*/


/*
Ici, pour chaque usine on somme la volume d'eau reçu par les sources.*/
                /*sscanf(chaine, "%[^;];%[^;];%d;%d;%d",
                    perso.listedescapacites[j].nom,
                    perso.listedescapacites[j].description,
                    &perso.listedescapacites[j].damage,
                    &perso.listedescapacites[j].type,
                    &perso.listedescapacites[j].cd);*/
pAVL VolumeCapte(FILE * fileUsine, FILE * filesource)
{
    char line[50]; 
    int h;
    char IDUsine[128];
    char IDSource[128];
    int volumeSource;
    int volumeMaxUsine;
    pAVL elmt;
    if(fileUsine && fileUsine)
    {
        pAVL AVL_VC = NULL;
        while(fgets(line,sizeof(line),fileUsine))
        {
            sscanf(line, "%[^;];%d",
                IDUsine,
                &volumeMaxUsine);
        }
        while(fgets(line, sizeof(line),filesource))
        {
            sscanf(line, "%[^;];%[^;];%d",
                IDSource,
                IDUsine,
                &volumeSource);
            if (!(elmt = recherche(AVL_VC, IDUsine)))
            {
                AVL_VC = insertionAVL(AVL_VC,IDUsine, &h);
            }
            else 
            {
                elmt->Total_Source_Vol += volumeSource;
            }
        }

        /*while(fgets(line,sizeof(line),fileUsine))
        {
            sscanf(line, "%[^;];%d",
                IDUsine,
                &volumeMaxUsine);
            
            pAVL elmt1 = recherche(AVL_VC, IDUsine);
            if(elmt1)
            {
                elmt1->Capacity_Max = volumeMaxUsine;
                if (elmt1->Capacity_Max < elmt1->Total_Source_Vol)
                {

                }
            }
        }*/



    }
    else 
    {
        printf("Le fichier reçu est vide!\n");
    }
}

pAVL VolumeTraite()
{

}

int ProjetHISTO(pAVL histo, int key)
{

}