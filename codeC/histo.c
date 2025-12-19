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


void VolumeCapte(FILE * filesource) //src
{
    char line[128]; 
    int h;
    char IDUsine[128];
    char IDSource[128];
    int volumeSource;
    pAVL elmt;
    pAVL AVL_VC = NULL;
    if(filesource)
    {
        //printf(VERT"On fait la partie src\n"RESET);
        while (fgets(line, sizeof(line), filesource))
        {
            if (sscanf(line, "%[^;];%[^;];%d", IDSource, IDUsine, &volumeSource) != 3) continue;
            elmt = recherche(AVL_VC, IDUsine);
            if (!elmt)
            {
                //printf(VIOLET"L'usine %s n'est pas dans l'AVL, on l'ajoute\n"RESET,IDUsine);
                h = 0;
                AVL_VC = insertionAVL(AVL_VC, IDUsine, &h,AVL_HISTO);
                elmt = recherche(AVL_VC, IDUsine);
            }
            elmt->data.HistoPart->Total_Source_Vol += volumeSource;
        }        

    }
    else 
    {
        printf("Le fichier reçu est vide!\n");
    }
    
    /*On cree le fichier return*/

    FILE * returnSRC = fopen("returnsrc.txt", "w");
    if (returnSRC) parcoursprefixe(AVL_VC, returnSRC,SRC);        
    else printf(ROUGE"returnSRC n'existe pas!\n"RESET);
    suppressionAVL(AVL_VC);
    
}

void VolumeTraite(FILE * filesourceL) //real
{
    char line[128]; 
    int h;
    char IDUsine[128];
    char IDSource[128];
    int volumeSource;
    float leaks;
    pAVL elmt;
    pAVL AVL_VT = NULL;
    if(filesourceL)
    {
        //printf(VERT"On fait la partie real\n"RESET);
        while (fgets(line, sizeof(line), filesourceL))
        {
            if (sscanf(line, "%[^;];%[^;];%d;%f", IDSource, IDUsine, &volumeSource, &leaks) != 4) continue;
            elmt = recherche(AVL_VT, IDUsine);
            if (!elmt)
            {
                //printf(VIOLET"L'usine %s n'est pas dans l'AVL, on l'ajoute\n"RESET,IDUsine);
                h = 0;
                AVL_VT = insertionAVL(AVL_VT, IDUsine, &h,AVL_HISTO);
                elmt = recherche(AVL_VT, IDUsine);
            }
            elmt->data.HistoPart->Total_Real_Vol += volumeSource - (volumeSource * (leaks / 100));
        }        

    }
    else 
    {
        printf("Le fichier reçu est vide!\n");
    }    

    //On cree le fichier return
    FILE * returnREAL = fopen("returnreal.txt", "w");
    if (returnREAL) ;
    else printf(ROUGE"returnREAL n'existe pas!\n"RESET);

    parcoursprefixe(AVL_VT, returnREAL,REAL);  
    suppressionAVL(AVL_VT); 
    fclose(returnREAL); 
}



